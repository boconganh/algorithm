process.stdin.resume();
process.stdin.setEncoding('utf8');


var B=1000000;
var C=6;

function toarray(x){
    return [].slice.call(x);
}
function stoa(s){
    var n=s.length;
    var nd=n;
    var res=[];
    
    var st;
    while(nd>0){
        st=(nd-C)>0?(nd-C):0;
        //console.log(st,nd);
        res.push(parseInt(s.slice(st,nd)));
        nd=st;
    }
   
    return res;
}
function div(a,b){
    return Math.floor(a/b);
}
function cmp(a,b){
    if(a<b) return -1;
    if(a>b) return 1;
    return 0;
}
function log(){
    var args=toarray(arguments);
    args.forEach(function(v){
        if(v){
            if(typeof v.toString==="function"){
                console.log(v.toString()); 
            }else{
                console.log(v);
            }
        }
    });
}
function tos(n){
    var s=n.toString();
    var out="";
    for(var i=0;i<C-s.length;++i){
        out=out+"0";
    }
    return out+s;
}
function Num(s){
    
    if(typeof s==="undefined"){
        this.sign=1;
        this.a=[];
        return this;
    }
    if(typeof(s)==="number"){
        //console.log("Number");
        
        if(s<0){
            this.sign=-1;
            s=-s;
        }else{
            this.sign=1;
        }
        this.a=[]
        while(s){
            this.a.push(s%B);
            //console.log(s);
            s=div(s,B);
        }
        
    }else if(typeof s==="string"){
        //console.log("String");
        if(s[0]==="-"){
            this.sign=-1;
            this.a=stoa(s.slice(1,s.length));
        }else{
            this.sign=1;
            this.a=stoa(s);
        }
    }
}

Num.prototype.toString=function(){
    
    if(this.a.length===0){
        return "0";
    }
    var out="";
    if(this.sign<0){
        out="-";
    }
    var i=this.a.length-1;
    out=out+this.a[i].toString();
    for(--i;i>=0;--i){
        out=out+tos(this.a[i]);
    }
    return out;
}
Num.prototype.trim=function(){
    while(this.a.length!==0 && this.a[this.a.length-1]===0){
        this.a.pop();
    }
    if(this.a.length===0){
        this.sign=1;
    }
}
Num.prototype._add=function(o){
    var i;
    var n1=this.a.length,n2=o.a.length;
    var m=0;
    var res=new Num();

    for(i=0;i<Math.max(n1,n2);++i){
        
        m+=(i<n1?this.a[i]:0)+(i<n2?o.a[i]:0);
        
        res.a.push(m%B);
        m=div(m,B);
    }
    while(m){
       
        res.a.push(m%B);
        m=div(m,B);
    }
    return res;
}
Num.prototype._sub=function(o){
    var i;
    var n1=this.a.length,n2=o.a.length;
    var t,m=0;
    var res=new Num();

    for(i=0;i<Math.max(n1,n2);++i){
        
        t=m+(i<n1?this.a[i]:0)-(i<n2?o.a[i]:0);
        if(t<0){
            m=-1;
            t+=B;
        }else{
            m=0;
        }
      
        res.a.push(t);
       
    }
    res.trim();
    return res;
}


function complex(r,i){
    var args=toarray(arguments);
    //log(args.length===1);
    if(args.length===0){
        this.r=0;
        this.i=0;
    }else if(args.length===1){
        //log("case 1");
        this.r=(args[0]);
        this.i=0;
    }else{
        // log("case 2");
        this.r=(args[0]);
        this.i=(args[1]);
        //log(args);
    }
}



complex.prototype={
    add:function(o){
        return new complex(this.r+o.r,this.i+o.i);
    },
    sub:function(o){
        return new complex(this.r-o.r,this.i-o.i);
    },
    mul: function(o){
        return new complex(this.r*o.r-this.i*o.i,this.r*o.i+this.i*o.r);
    },
    conj:function(){
        return new complex(this.r,-this.i);
    }
};
complex.prototype.toString=function(){
    return this.r.toString()+" + "+this.i.toString()+"i";
}

function fft(x){
    var n=x.length;
    if(n<2) return;
    var odd=new Array(n/2);
    var even=new Array(n/2);
    for(var i=0;i<n/2;++i){
        odd[i]=x[2*i+1];
        even[i]=x[2*i];
    }
    //log(odd,even);
    fft(even);
    fft(odd);
   
    for(var k=0;2*k<n;++k){
        var w=new complex(Math.cos(Math.PI*2*k/n),-Math.sin(Math.PI*2*k/n));
        var t=w.mul(odd[k]);
        x[k]=even[k].add(t);
        x[k+n/2]=even[k].sub(t);
    }
}

function ifft(x){
    var xx=x.map(function (v){
        return v.conj();
    });
    fft(xx);
    var n=x.length;
    for(var i=0;i<n;++i){
        x[i]=new complex(xx[i].r/n,xx[i].i/n);
    }
}

Num.prototype.mul=function (o){
    var n1=this.a.length,n2=o.a.length;
    var n=2;
    while(n<n1+n2){
        n=n*2;
    }
    var fa=new Array(n),fb=new Array(n);
    var i;
    for(i=0;i<n1;++i){
        fa[i]=new complex(this.a[i]);
    }
    for(;i<n;++i){
        fa[i]=new complex();
    }
    for(i=0;i<n2;++i){
        fb[i]=new complex(o.a[i]);
    }
    for(;i<n;++i){
        fb[i]=new complex();
    }
    
    fft(fa);
    fft(fb);
    for(i=0;i<n;++i){
        fa[i]=fa[i].mul(fb[i]);
    }
    ifft(fa);
    var res=new Num();
    var t=0;
    for(i=0;i<n;++i){
        t+=Math.round(fa[i].r);
        res.a.push(t%B);
        t=div(t,B);
    }
    res.sign=this.sign*o.sign;
    res.trim();
    return res;
}


Num.prototype._cmp=function(o){
    if(cmp(this.a.length,o.a.length)!==0){
        return cmp(this.a.length,o.a.length);
    }
    var i=this.a.length-1;
    for(;i>=0;--i){
        if(cmp(this.a[i],o.a[i])!==0){
            return cmp(this.a[i],o.a[i]);
        }
    }
    return 0;
    
}

Num.prototype.cmp=function(o){
    if(cmp(this.sign,o.sign)){
        return cmp(this.sign,o.sign);
    }
    return this.sign*this._cmp(o);
}
Num.prototype.add=function (o){
    var res;
    if(this.sign==o.sign){
        res=this._add(o);
        res.sign=this.sign;
        return res;
    }else{
        if(this._cmp(o)>=0){
            res=this._sub(o);
            res.sign=this.sign;
        }else{
            res=o._sub(this);
            res.sign=o.sign;
        }
        return res;
    }
}
Num.prototype.sub=function (o){
    var res;
    if(this.sign!=o.sign){
        res=this._add(o);
        res.sign=this.sign;
        return res;
    }else{
        if(this._cmp(o)>=0){
            res=this._sub(o);
            res.sign=this.sign;
        }else{
            res=o._sub(this);
            res.sign=-this.sign;
        }
        return res;
    }
}
Num.ONE=new Num(1);

function _pow (a,p) {
	var res=new Num(1);
	var t=new Num();
	t.a=a.a.slice();
	t.sign=a.sign;
	while(p){
		if(p%2===1){
			res=res.mul(t);
		}
		t=t.mul(t);
		p>>=1;
	}
	return res;
}

Num.prototype.pow=function (p){
	return _pow(this,p);
}

var s="";

process.stdin.on("data",function (chunk) {
	s+=chunk;	
});

process.stdin.on("end",function (){
	var a=s.split(/\s+/);
	var n=new Num(a[0]),p=parseInt(a[1]);
	var out=n.pow(p).toString();
	var i;
	for(i=0;i<out.length;++i){
		if(i!==0 && i%70===0){
			process.stdout.write("\n");
		}
		process.stdout.write(out[i]);
	}
});
