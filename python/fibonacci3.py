class matrix:
	def __init__(self,a):
		self.a=a
		self.m=len(a)
		self.n=len(a[0])
	def __mul__(self,o):
		
		#kiem tra 2 ma tran nhan dc voi nhau khong?
		assert(self.n==o.m)
	
		a=[]
		for j in range(self.m):
			a.append([])
			for i in range(o.n):
				s=0
				for k in range(o.m):
					s+=self.a[j][k]*o.a[k][i]
				a[j].append(s)
		return matrix(a)
	
	def __pow__(self,p):
		
		#kiem tra ma tran vuong?
		assert(self.m==self.n)
		
		a=[]
		for j in range(self.n):
			a.append([])
			for i in range(self.n):
				
				if i==j: a[j].append(1)
				else: a[j].append(0)
		r=matrix(a)
		
		while p:
			if p%2:
				r=r*self
			self=self*self
			p>>=1
		return r
	def __str__(self):
		s="---- matrix [{0} x {1}] ----\n".format(len(self.a),len(self.a[0]))
		for i in range(len(self.a)):
			s+=str(self.a[i])+"\n"
		return s

a=matrix([[1,1],[1,0]])
first=matrix([[1,1]])
b=a**30000
r=first*b
print (b.a[0][0])
