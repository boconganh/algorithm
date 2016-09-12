

def insert_sort(A):
	for j in xrange(1,len(A)):
		key=A[j]
		i=j-1
		while i>=0 and A[i]>key:
			A[i+1]=A[i]
			i-=1
		A[i+1]=key

A=[32,1,2]
print A
insert_sort(A)
print A