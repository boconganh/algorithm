a=[(1,2),(1,3),(2,6),(2,4),(3,5)]
"""

		1
	2      3
	
6      4    5
"""

l=[[],[2,3],[6,4],[5],[],[],[]]

def euler_tour(u,res,depth=0):
	
	res.append((u,depth))
	for v in l[u]:
		
		euler_tour(v,res,depth+1)
		res.append((u,depth))
		
res=[]
euler_tour(1,res)
print res
	
