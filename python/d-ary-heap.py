import math
from sys import *

class Node:
	def __init__(s,key,val):
		s.key=key
		s.val=val
	def __str__(s):
		return "{key: %d,val: %d}"%(s.key,s.val)

class Heap:
	def __init__(s,ary=4):
		s.data=[]
		s.ary=ary
	
	def parent(s,x):
		if x==0: return None
		return int(math.ceil(x/s.ary))
	def child(s,x):
		return iter(range(s.ary*x+1,min(s.ary*(x+1)+1,len(s.data))))
	def minchild(s,x):
		minpos=minkey=None
		for i in s.child(x):
			if minkey is None or s.data[i].key<minkey:
				minpos,minkey=i,s.data[i].key
		return minpos
	def siftup(s,hi,pos):
		p=s.parent(pos)
		while p is not None and s.data[p].key>hi.key:
			s.data[pos]=s.data[p]
			s.data[pos].pos=pos
			pos=p
			p=s.parent(pos)
			
		s.data[pos]=hi
		s.data[pos].pos=pos
	def siftdown(s,hi,pos):
		c=s.minchild(pos)
		while c is not None and s.data[c].key<hi.key:
			s.data[pos]=s.data[c]
			s.data[pos].pos=pos
			pos=c
			c=s.minchild(pos)
		s.data[pos]=hi
		s.data[pos].pos=pos
	def insert(s,k,v):
		hi=Node(k,v)
		s.data.append(None)
		s.siftup(hi,len(s.data)-1)
		return hi

	def size(s):
		return len(s.data)

	def extractmin(s):
		i=s.data[0]
		last=s.data[-1]
		s.data.pop()
		if len(s.data):
			s.siftdown(last,0)
		return i
	def decreasekey(s,hi,newkey):
		hi.key=newkey
		s.siftup(hi,hi.pos)
