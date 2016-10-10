import math

def fft(x):
  n=len(x)
  if n<2: return
  odd=x[1::2]
  even=x[::2]
  fft(odd)
  fft(even)
  #print(n,odd,even)
  for k in range(n//2):
      w=odd[k]* math.e**(-2j*math.pi*k/n)
      x[k]=even[k]+w
      x[k+n//2]=even[k]-w

def ifft(x):
  x[:]=map(lambda x: x.conjugate(),x)
  fft(x)
  n=len(x)
  x[:]=map(lambda x: x.conjugate()/n,x)


def mul(a,b):
	
	x=a[:]
	y=b[:]
	n=2
	while n<len(x)+len(y):
		n<<=1
	x.extend([0]*(n-len(x)))
	y.extend([0]*(n-len(y)))
	fft(x)
	fft(y)
	z=[]
	for i in range(n):
		z.append(x[i]*y[i])
	ifft(z)
	return z
a=[1,2,1]
b=[1,2,1]
print(mul(a,b))

