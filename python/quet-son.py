
mau={'T':0,'X':1,'V':2}

###### doc du lieu
n=input() # so phong

ds=[]  ## danh sach phong ma robot [i] phu trach
for i in range(n):
	ds.append([int(i) for i in raw_input().split()])
	
start=map(lambda i: mau[i],  raw_input())


###### init
MAX=1000000000
ret=MAX
result=[]

#### quay lui

def Try(i,robot,res):
	if i==n:
		for j in range(n):
			if res[j]!=0: ### mau của phòng thứ j không là màu trắng
				return
		global ret,result
		s=0  ### biến tính số lần quét
		
		for j in range(n):
			s+=robot[j]*len(ds[j])
		if s<ret:  ### cap nhat ket qua tot hon 
			ret=s
			result=[i for i in robot]
		return
	for j in range(3):
		robot[i]=j
		for k in ds[i]:  ### k lần lượt là các phòng mà robot thứ i phụ trách
			res[k-1]=(res[k-1]+j)%3  ### màu của phòng k  sau j lần quét sơn
		Try(i+1,robot,res)
		for k in ds[i]:
			res[k-1]=(res[k-1]-j)%3  ### trả lại trạng thái trước đó

robot=[0]*n
#print start ## start là trạng thái màu ban đầu của các phòng
Try(0,robot,start)

if ret<MAX:
	print ret
	#print result
	for i in range(n):
		for k in range(result[i]):
			print i+1,
	print
else:
	print -1
