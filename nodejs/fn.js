
String.prototype.lambda = function() {
    var params = [],
        expr = this,
        sections = expr.split(/\s*->\s*/m);
    if (sections.length > 1) {
        while (sections.length) {
            expr = sections.pop();
            params = sections.pop().replace(/^\s*(.*)\s*$/, '$1').split(/\s*,\s*|\s+/m);
            sections.length && sections.push('(function('+params+'){return ('+expr+')})');
        }
    } else if (expr.match(/\b_\b/)) {
        params = '_';
    } else {
        // test whether an operator appears on the left (or right), respectively
        var leftSection = expr.match(/^\s*(?:[+*\/%&|\^\.=<>]|!=)/m),
            rightSection = expr.match(/[+\-*\/%&|\^\.=<>!]\s*$/m);
        if (leftSection || rightSection) {
            if (leftSection) {
                params.push('$1');
                expr = '$1' + expr;
            }
            if (rightSection) {
                params.push('$2');
                expr = expr + '$2';
            }
        } else {
            // `replace` removes symbols that are capitalized, follow '.',
            // precede ':', are 'true', 'false', 'null', 'undefined', 'this'
            // or 'arguments'; and also the insides of strings (by a crude test).
            // `match` extracts the remaining symbols.
            var vars = this.replace(/(?:\b[A-Z]|\.[a-zA-Z_$])[a-zA-Z_$\d]*|[a-zA-Z_$][a-zA-Z_$\d]*\s*:|true|false|null|undefined|this|arguments|'(?:[^'\\]|\\.)*'|"(?:[^"\\]|\\.)*"/g, '').match(/([a-z_$][a-z_$\d]*)/gi) || []; // '
            for (var i = 0, v; v = vars[i++]; )
                params.indexOf(v) >= 0 || params.push(v);
        }
    }
    return new Function(params, 'return (' + expr + ')');
}

String.prototype.fn=function (){
	var body = this;
	if (body.match(/\breturn\b/))
	return new Function(this);
	return this.lambda();
};

Function.prototype.fn=function (){
	return this;
}

function fn(value){
 	return value.fn();
}

var map = function(f, sequence, object) {
    f = fn(f);
    var len = sequence.length,
        result = new Array(len);
    for (var i = 0; i < len; i++)
        result[i] = f.apply(object, [sequence[i], i]);
    return result;
}

var compose = function(/*fn...*/) {
    var fns = map(fn, arguments),
        arglen = fns.length;
    return function() {
        for (var i = arglen; --i >= 0; )
            arguments = [fns[i].apply(this, arguments)];
        return arguments[0];
    }
}

var reduce = function(f, init, sequence, object) {
    f = fn(f);
    var len = sequence.length,
        result = init;
    for (var i = 0; i < len; i++)
        result = f.apply(object, [result, sequence[i]]);
    return result;
}

var select = function(f, sequence, object) {
    f=fn(f);
    var len = sequence.length,
        result = [];
    for (var i = 0; i < len; i++) {
        var x = sequence[i];
        f.apply(object, [x, i]) && result.push(x);
    }
    return result;
}

var foldr = function(f, init, sequence, object) {
    f=fn(f);
    var len = sequence.length,
        result = init;
    for (var i = len; --i >= 0; )
        result = f.apply(object, [sequence[i], result]);
    return result;
}

var every = function(f, sequence, object) {
    f=fn(f);
    var len = sequence.length,
        value = true;
    for (var i = 0; i < len; i++)
        if (!(value = f.call(object, sequence[i])))
            break;
    return value; 
}

console.log(every('>0',[1,2,3,4,5,6]));

