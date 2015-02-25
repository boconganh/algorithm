#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define maxn  1000
#define max2(a,b) ((a)>(b)?(a):(b))
#define min2(a,b) ((a)<(b)?(a):(b))

typedef struct bigint{
	char digit[maxn]; // dung mang co dinh de khong phai giai phong bo nho
	// bieu dien so lon =  a_0+a_1*10+... a_i*10^i
	int len;
}bigint;

void read(bigint *a){
	int i,n;
	scanf("%s",a->digit);
	n=strlen(a->digit);
	a->len=n;
	for(i=0;i<n;++i){
		a->digit[i] -='0';
	}
	
	// dao nguoc so
	int t;
	for(i=0;i<n/2;++i){
		t=a->digit[i];
		a->digit[i]=a->digit[n-1-i];
		a->digit[n-1-i]=t;
	}
}
void show(const bigint *a){
	int i;
	if(a->len==0){
		printf("0");
	}else{
		for(i=a->len-1;i>=0;--i){
			putchar('0'+a->digit[i]);
		}
	}
	printf("\n");
}

void copy(const bigint *source,bigint *dest){
	int i;
	for(i=0;i<source->len;++i){
		dest->digit[i]=source->digit[i];
	}
	dest->len=source->len;
}
void trim(bigint *a){
	while(a->len && a->digit[a->len-1]==0) a->len--;
}
void add(const bigint *a,const bigint *b,bigint *c){
	int i;
	int m=0;
	for(i=0;i<max2(a->len,b->len);++i){
		m += (i<a->len? a->digit[i]:0) + (i<b->len?b->digit[i]:0);
		c->digit[i]=m%10;
		m/=10;
	}
	while(m){
		c->digit[i++]=m%10;
		m/=10;
	}
	c->len=i;
}

void sub(const bigint *a,const bigint *b,bigint *c){ // gia su a>=b
	int i;
	int t=0,m=0;
	for(i=0;i<a->len;++i){
		t=a->digit[i]-(i<b->len?b->digit[i]:0)+ m;
		if(t<0){
			m=-1;
			c->digit[i]=t+10;
		}else{
			m=0;
			c->digit[i]=t;
		}
	}
	c->len=i;
	trim(c);
}


void mul_int(const bigint *a,int n,bigint *c){
	int i,t=0;
	for(i=0;i<a->len;++i){
		t+=a->digit[i]*n;
		c->digit[i]=t%10;
		t/=10;
	}
	while(t){
		c->digit[i++]=t%10;
		t/=10;
	}
	c->len=i;
	trim(c);
}

void shift(bigint *a,int k){ // a= a*10^k
	if(!a->len) return;
	int i;
	for(i=a->len-1;i>=0;--i){
		a->digit[i+k]=a->digit[i];
	}
	for(i=0;i<k;++i){
		a->digit[i]=0;
	}
	a->len+=k;
}

void mul_naive(const bigint *a,const bigint *b,bigint *c){
	bigint res;
	res.len=0;
	bigint t;
	
	int i;
	for(i=a->len-1;i>=0;--i){
		mul_int(b,a->digit[i],&t);
		shift(&res,1);
		add(&res,&t,&res);
	}
	copy(&res,c);
}

void split_at(const bigint *a,int k,bigint *lo,bigint *hi){
	int i;
	lo->len=min2(a->len,k);
	for(i=0;i<lo->len;++i){
		lo->digit[i]=a->digit[i];
	}
	hi->len=0;
	for(;i<a->len;++i){
		hi->digit[hi->len++]=a->digit[i];
	}
}
void mul_karatsuba(const bigint *a,const bigint *b,bigint *c){
	if(a->len<10 || b->len<10){
		mul_naive(a,b,c);
		return;
	}
	int m=max2(a->len,b->len);
	int m2=m/2;
	bigint lo1,hi1,lo2,hi2;
	bigint z0,z1,z2;
	
	split_at(a,m2,&lo1,&hi1);
	split_at(b,m2,&lo2,&hi2);
	
	bigint t1,t2;
	add(&lo1,&hi1,&t1);
	add(&lo2,&hi2,&t2);
	
	mul_karatsuba(&lo1,&lo2,&z0);
	mul_karatsuba(&t1,&t2,&z1);
	mul_karatsuba(&hi1,&hi2,&z2);
	
	add(&z0,&z2,&t1);
	sub(&z1,&t1,&t2);
	
	shift(&z2,2*m2);
	shift(&t2,m2);
	add(&z0,&z2,&z0);
	add(&z0,&t2,&z0);
	copy(&z0,c);
	
}
int main() {
	bigint a,b,c;
	read(&a);
	read(&b);
	show(&a);
	show(&b);
	mul_naive(&a,&b,&c);
	show(&c);
	mul_karatsuba(&a,&b,&c);
	show(&c);
	return 0;
}
