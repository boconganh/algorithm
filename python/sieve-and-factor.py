def sieve(n):
    ''' sàng nguyên tố [0,n] '''
    
    danh_dau=[True]*(n+1) # giả sự lúc đầu đều có thể là snt
    
    can_n=int(n**0.5)+1 # = floor(sqrt(n))+1
    
    for i in range(2,can_n+1): # i= 2->can_n
        if danh_dau[i]: # i là số nguyên tố
            
            for j in range(i*i,n+1,i): # j=i*i, i*i+i , ...,n
                danh_dau[j]=False ## j khong là số nguyên tố
    
    
    primes=[]
    for i in range(2,n+1): #i= 2->n
        if danh_dau[i]: primes.append(i) #liệt kê lại số nguyên tố vào mảng mới
    return primes

print sieve(100)
"""
#output:
[2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97]
"""

def gen_sieve_table(n):
    
    ''' sàng nguyên tố [0,n] '''
    
    danh_dau=[0]*(n+1) # giả sự lúc đầu đều có thể là snt
    
    can_n=int(n**0.5)+1 # = ceil(sqrt(n))+1
    
    for i in range(2,can_n+1): # i= 2->can_n
        if danh_dau[i]==0: # i là số nguyên tố -> giá trị =0 [không có ước nguyên tố nhỏ hơn #1]
            
            for j in range(i*i,n+1,i): # j=i*i, i*i+i , ...,n
                danh_dau[j]=i ## j khong là số nguyên tố
    
    
    return danh_dau
    

def factor(n,sieve_table):
    if sieve_table[n]==0: ## là số nguyên tố trả lại ước là chính nó
        return [n] 
    else:
        d=sieve_table[n]  ## chứa 1 ước nguyên tố nhỏ nhất là d
        return [d] + factor(n//d,sieve_table)

sieve_table=gen_sieve_table(100000)

print factor(12345,sieve_table)

"""
output:
[5, 3, 823]
"""
