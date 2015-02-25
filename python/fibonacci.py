def f(n):
	if n<2: return 1
	fn_1=1
	fn_2=1
  	i=2
	while i<=n:
		fn=fn_1+fn_2
		fn_2=fn_1
		fn_1=fn
		i+=1
	return fn

print(f(30000)) 
