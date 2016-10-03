


class Poly:
    def __init__(self,a=[]):
        self.a=a[:]
        self.degree=len(self.a)
    def __add__(self,other):
        degree=max(self.degree,other.degree)
       
        a=[0]*degree
        for i in range(degree):
           
            a[i]=(self.a[i] if i<self.degree else 0)+(
                other.a[i] if i<other.degree else 0)
        return Poly(a)
    def __sub__(self,other):
        degree=max(self.degree,other.degree)
       
        a=[0]*degree
        for i in range(degree):
           
            a[i]=(self.a[i] if i<self.degree else 0)-(
                other.a[i] if i<other.degree else 0)
        while len(a)>0 and a[-1]==0:
            a.pop()
        return Poly(a)
    def __repr__(self):
        if self.degree==0:
            return ''
        s=str(self.a[0])
        for i,v in enumerate(self.a[1:]):
            s+=' + %r*x^%d'%(v,i+1)
        return s
    def __rshift__(self,k): # return f(x)*x^k
        degree=self.degree+k
        a=[0]*k+self.a[:]
        return Poly(a)
    def __mul__(self,other):
        if isinstance(other,int) or isinstance(other,float):
            a=map(lambda x:x*other,self.a)
            return Poly(a)
        if isinstance(other,Poly):
            ans=Poly()
            for i,v in enumerate(other.a):

                ans=ans+((self*v)>>i)
            return ans

    def __div__(self,other):

        q=Poly()

        t=self
        while t.degree>=other.degree:
            x=(Poly([1])*(1.0*t.a[-1]/other.a[-1])>>(t.degree-other.degree))
            t=t-other*x
            q=q+x
        return (q,t)
        
            
        
b=Poly([1,2,1])
a=Poly([1,2,3,4])
print a+b
print a-b
print a*b
print a/b
