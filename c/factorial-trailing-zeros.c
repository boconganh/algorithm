#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>


#define maxb 801
typedef long long ll;
typedef long double ld;

ll f[maxb+1];
void init(){
	ll i;
	for(i=0;i<=maxb;++i){
		f[i]=0;
	}
	for(i=2;i*i<=maxb;++i){
		ll j;
		if(f[i]) continue;
		j=i;
		while(j*i<=maxb){
			f[j*i]=i;
			j++;
		}
	}
}

ll ft[50];
int fn;
ll fnx[50];
int cnx[50],cn;

int cmpll(const void *x,const void *y){
	return *(ll*)x-*(ll*)y;
}

void factor(ll n){
	if(n<2) return;
	if(f[n]==0){
		ft[fn++]=n;
		return;
	}
	if(fn>20) return;
	factor(n/f[n]);
	ft[fn++]=f[n];
}

void genfactor(ll n){
	fn=0;
   	cn=0;
   	
    int i;
    
   	factor(n);
   	
   	for(i=0;i<fn;++i){
   		if(cn==0 || ft[i]!=ft[i-1]){
   			fnx[cn]=ft[i];
   			cnx[cn]=1;
   			cn++;
   		}else{
   			cnx[cn-1]++;
   		}
   	}
}

ll zeros_(ll n,ll p){
	ll t=n,res=0;
	while(t){
		res+=t/p;
		t/=p;
	}
	return res;
}

ll zeros(ll n,ll b){
	genfactor(b);
	ll res=LLONG_MAX;
	int i;
	for(i=0;i<cn;++i){
		ll t=zeros_(n,fnx[i])/cnx[i];
		if(t<res) res=t;
	}
	return res;
}

ll digits(ll _n,ll _b){
	ld n=(ld)_n,b=(ld)_b;
	ld res=floorl(1.0+(logl(2.0*n*M_PI)/2.0+n*logl(n)-n)/logl(b));
	return (ll)res;
}
ll digits_upper(ll _n,ll _b){
	ld n=(ld)_n,b=(ld)_b;
	ld res=floorl(1.0+(logl(2.0*n*M_PI)/2.0+n*logl(n)-n + n/12.0)/logl(b));
	return (ll)res;
}

#define maxn 1000000
ld d[maxn+1];
ld d2[maxn+1];
void gen(){
	d[1]=0;
	int i;
	for(i=2;i<=maxn;++i){
		d[i]=d[i-1]+logl((ld)i);
	}
}

int main(void) {
	init();
	gen();
	int i;
	/*
	for(i=2;i<=maxb;++i){
		if(!f[i]) printf("%lld ",i);
	}
	*/
	/*
	genfactor(340);
	for(i=0;i<cn;++i){
		printf("%lld %d\n",fnx[i],cnx[i]);
	}
	*/
	//printf("%lld\n",zeros(20,10));
	ll n,b;
	while(scanf("%lld%lld",&n,&b)==2){
		if(n>=maxn){
			printf("%lld %lld\n",zeros(n,b),digits(n,b));
		}else{
			printf("%lld %lld\n",zeros(n,b),(ll)ceill(d[n]/logl(b)));
		}
	}
	return 0;
}
