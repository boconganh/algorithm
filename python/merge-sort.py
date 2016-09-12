def merge(A,p,q,r):
	n1=q-p+1
	n2=r-q
	L=A[p:p+n1]+[float("inf")]
	R=A[q+1:q+1+n2]+[float("inf")]
	#print A[p:r+1],L,R
	i=0
	j=0
	for k in range(p,r+1):
		if L[i]<=R[j]:
			A[k]=L[i]
			i+=1
		else:
			A[k]=R[j]
			j+=1


def merge_sort(A,p,r):
	if p<r:
		q=(p+r)//2
		merge_sort(A,p,q)
		merge_sort(A,q+1,r)
		merge(A,p,q,r)

A=[1,2,4,2,4,32,45,6]
print A
merge_sort(A,0,len(A)-1)
print A
