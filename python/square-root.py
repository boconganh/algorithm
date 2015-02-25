# your code goes here
def sqrt(n):
	x=1

	while True :
		print "---"
		yc=n//x
		print yc
		y=x+yc
		
		print x
		yc=y//2
		print y
		print yc
		t=x-yc
		if t==0 or t==-1: return x
		x=yc

print sqrt(25526843095193542086512684085507351158577087351779)
