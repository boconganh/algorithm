from sys import *
from bisect import *

def index(a, x):
    'Locate the leftmost value exactly equal to x'
    i = bisect_left(a, x)
    if i != len(a) and a[i] == x:
        return i
    raise ValueError

def find_lt(a, x):
    'Find rightmost value less than x'
    i = bisect_left(a, x)
    if i:
        return i-1
    raise ValueError

def find_le(a, x):
    'Find rightmost value less than or equal to x'
    i = bisect_right(a, x)
    if i:
        return i-1
    raise ValueError

def find_gt(a, x):
    'Find leftmost value greater than x'
    i = bisect_right(a, x)
    if i != len(a):
        return i
    raise ValueError

def find_ge(a, x):
    'Find leftmost item greater than or equal to x'
    i = bisect_left(a, x)
    if i != len(a):
        return i
    raise ValueError

f=[1,1]
i=2
while i<510:
	f.append(f[i-2]+f[i-1])
	i+=1
for line in stdin.readlines():
	a,b=[int(i) for i in line.split()]
	if a==0 and b==0:
		break
	u=find_ge(f,a)
	v=find_le(f,b)
	stdout.write(str(v-u+1)+"\n")
