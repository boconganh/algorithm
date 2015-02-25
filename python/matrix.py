from copy import *
from fractions import *
from sys import *
class Matrix:
	def __init__(self,a,cp=False):
		""" cp : copy or use a as matrix """
		self.m=len(a)
		self.n=len(a[0])
		if cp:
			self.a=deepcopy(a)
		else:
			self.a=a
	def __mul__(self,o):
		assert(self.n==o.m)
		a=[]
		for j in range (self.m):
			a.append([])
			for i in range(o.n):
				s=0
				for k in range(self.n):
					s+=self.a[j][k]*o.a[k][i]
				a[j].append(s)
		return Matrix(a)
	
	def det(self):
		""" O(n^3)"""
		assert(self.m==self.n)
		Zero=Fraction(0)
		## copy to  Matrix Fraction element ##
		a=[]
		for i in range(self.n):
			a.append([])
			for j in range(self.n):
				a[i].append(Fraction(self.a[i][j]))
		s=Matrix(a)
		ret=Fraction(1)
		## start compute ##
		for i in range(s.n):
			for j in range(i+1,s.n):
				if s.a[i][i]==Zero:
					for k in range(i+1,s.n):
						if s.a[k][i]!=Zero:
							s.a[k],s.a[i]=s.a[i],s.a[k]
							break
					#swap 2 row 
					ret=-ret
					if k==s.n:
						return s.a[0][0].__class__(Zero)
				t=s.a[j][i]/s.a[i][i]
				for k in range(i,s.n): s.a[j][k]-=s.a[i][k]*t
                for i in range(s.n):
			ret*=s.a[i][i]
		## cast to class self.a[][]
		return self.a[0][0].__class__(ret)
	def inv(self):
		""" O(n^3) """
		assert (self.m==self.n)
		Zero=Fraction(0)
		d=Fraction(self.det())
		if d==Zero:
			raise ("|M|=0")
		a=[]
		for i in range(self.n):
			a.append([])
			for j in range(self.n):
				t=[]
				for u in range(self.n):
					if u==j:continue
					t.append([])
					for v in range(self.n):
						if v==i: continue
						t[-1].append(self.a[u][v])
				if (i+j) %2:
					dd=-1
				else: dd=1
				a[-1].append(dd*Fraction(Matrix(t).det())/d)
		return Matrix(a)
#giai he pt a*x=y
a=Matrix([
	[1,1,1,1],#=1
	[8,4,2,1],#=5
	[27,9,3,1],#=14
	[64,16,4,1]#30
	])
y=Matrix([[1],[5],[14],[30]])
x=a.inv()*y
print x.a
