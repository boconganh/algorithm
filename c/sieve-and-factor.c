#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxn 1000000

int a[maxn+1];
int primes[maxn],primes_len;
void sieve(){
    int i,j;
    memset(a,sizeof(int)*(maxn+1),0);
    for(i=2;i*i<=maxn;++i){
        if(a[i]) continue; //i la hop so
        for(j=i*i; j<=maxn;j+=i){ // cac so la boi cua i tu i*i ->n
            a[j]=i;  // cai nay luu lai so nguyen to nho nhat ma j chia het cho i
        }
    }
    /// liet ke lai so nguyen to
    
    primes[0]=2;
    primes_len=1;
    for(i=3;i<=maxn;i+=2){
        if(a[i]) continue;
        primes[primes_len]=i;
        primes_len++;
    }
    
}

int ft[50],fn;

void recrusive_factor(int n){
    if(!a[n]){
        ft[fn]=n;
        fn++;
    }else{
        recrusive_factor(n/a[n]);
        ft[fn]=a[n];
        ++fn;
        
    }
}

void factor(int n){
    fn=0;
    recrusive_factor(n);
}

int main() {
    
    sieve();
    
    printf("so luong so nguyen to <= (%d) = %d\n",maxn,primes_len);
    int n=12345;
    printf("phan tich thua so nguyen to %d=",n);
    factor(n);
    int i;
    
    for(i=0;i<fn-1;++i){
        printf("%d*",ft[i]);
    }
    printf("%d\n",ft[fn-1]);
    return 0;
}
