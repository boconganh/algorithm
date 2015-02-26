var log=console.log;

function Complex (r,i) {
	
  var newObject = Complex.prototype.isPrototypeOf(this)
                  ? this
                  : new Complex();
  newObject.r = r||0;
  newObject.i = i||0;
  return newObject;
}


Complex.prototype={
	
	add:function(o) {
		return Complex(this.r+o.r,this.i+o.i);
	},
	sub:function (o) {
		return Complex(this.r-o.r,this.i-o.i);
	},
	mul:function (o) {
		return Complex(this.r*o.r-this.i*o.i,this.r*o.i+this.i*o.r);
	},
	conj:function(){
		return Complex(this.r,-this.i);
	},
};
var a= Complex(1,2);

var b=Complex(3,5);

log(a.conj());
