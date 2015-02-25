from sys import *


n=8

kq=[0]*(n+1)
cheochinh=[True]*(2*n+4)
cheophu=[True]*(2*n+4)
cot=[True]*(n+1)

## init
res=0

def show():
	for i in range(1,n+1):
		for j in range(kq[i]-1): stdout.write("o")
		stdout.write("x")
		for j in range(n-kq[i]): stdout.write("o")
		stdout.write("\n")

def Try(i):
	global res
	for j in range(1,n+1):
		if cot[j] and cheochinh[i+j] and cheophu[i-j+n]:
			kq[i]=j
			cot[j]=False
			cheochinh[i+j]=False
			cheophu[i-j+n]=False
			
			if i!=n:
				Try(i+1)
			else:
				res+=1
				print kq[1:]
				show()
			cot[j]=True
			cheochinh[i+j]=True
			cheophu[i-j+n]=True
Try(1)

print "total: ",res
