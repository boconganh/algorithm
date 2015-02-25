#include <stdio.h>
#include <stdlib.h>

#define maxn 1000100

int vitri[maxn];
int out[maxn];
long gcd(long a,long b){
	if(a==0) return b;
	return gcd(b%a,a);
}
void solve(long p,long q){
	long t=gcd(p,q);
	
	p/=t;
	q/=t;
	//printf("%ld %ld\n",p,q);
	long int_part=p/q;
	long rem=p%q;
	long i;
	for(i=0;i<q;++i){
		vitri[i]=-1;
	}
	int open_brack,close_brack;
	i=0;
	for(;;){
		if(vitri[rem]>=0) break;
		vitri[rem]=i;
		rem*=10;
		out[i]=(int)(rem/q);
		//printf("%c\n",out[i]+'0');
		rem%=q;
		i++;
	}
	open_brack=vitri[rem];
	close_brack=i;
	//printf("%d %d\n",open_brack,close_brack);
	//show int_part
	printf("%ld.",int_part);
	
	//show
	for(i=0;i<open_brack;++i){
		printf("%d",out[i]);
	}
	
	//show repreat part
	printf("(");
	for(i=open_brack;i<close_brack;++i){
		printf("%d",out[i]);
	}
	printf(")\n");
}

int main(void) {
	int i,n;
	scanf("%d",&n);
	for(i=0;i<n;++i){
		long p,q;
		scanf("%ld%ld",&p,&q);
		solve(p,q);
	}
	return 0;
}
