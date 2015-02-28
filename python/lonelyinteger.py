import operator
def lonely(a):
  return reduce(operator.__xor__,a)

n=input()
a=map(int,raw_input().split())
print lonely(a)
