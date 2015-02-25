def fibo2(n):
	if n==0: return (1,1)
	if n==1: return (1,2)
	(a,b)=fibo2(n //2 -1)
	c=a+b
	if n%2:
		return (c*c - a*a, b*b + c*c)
	else:
		return (a*a + b*b, c*c - a*a)
		
print fibo2(300000)[0]
