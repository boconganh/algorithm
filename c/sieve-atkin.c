#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>


#define MAX 1000000

char array[MAX>>4];

typedef long long ll;

#define NP 1857860

long primes[NP];
long pn;

static int getBit(long i) {
	char block = array[(int) (i >> 4)];
	char mask = (char) (1 << ((i >> 1) & 7));
	
	return ((block & mask) != 0);
}

static void setBit(long i) {
	int index = (int) (i >> 4);
	char block = array[index];
	char mask = (char) (1 << ((i >> 1) & 7));
	
	array[index] = (char) (block | mask);
}

static void unSetBit(long i) {
	int index = (int) (i >> 4);
	char block = array[index];
	char mask = (char) (1 << ((i >> 1) & 7));
	
	array[index] = (char) (block & ~mask);
}

static void toggleBit(long i) {
	int index = (int) (i >> 4);
	char block = array[index];
	char mask = (char) (1 << ((i >> 1) & 7));
	
	array[index] = (char) (block ^ mask);
}

ll fnx[100];
int cnx[100],cn;

inline void factor(ll x){
	long i;
	cn=0;
	for(i=0;i<pn && primes[i]*primes[i]<=x;i++){
		while(x>0 && x%primes[i]==0){
			if(cn==0 || primes[i]!=fnx[cn-1]){
				fnx[cn]=primes[i];
				cnx[cn]=1;
				cn++;
			}else{
				cnx[cn-1]++;
			}
			x/=primes[i];
		}
	}
	if(x>1){
		fnx[cn]=x;
		cnx[cn]=1;
		cn++;
	}
}

int main(void) {
	
	long x,y,k,k1;
	double xUpper=sqrt(MAX/4)+1;
	long SQRT_MAX=(long)(sqrt(MAX)+1);
	long index;
	long sequence[]={2,4};
	
	while (x < xUpper) {
			index = 0;
			k1 = 4 * x * x;
			y = 1;
			if (x % 3 == 0) {
				while (1) {
					k = k1 + y * y;
					if (k >= MAX) {
						break;
					}
					toggleBit(k);
					y += sequence[(++index & 1)];
				}
			} else {
				while (1) {
					k = k1 + y * y;
					if (k >= MAX) {
						break;
					}
					toggleBit(k);
					y += 2;
				}
			}
			x++;
		}
	xUpper = sqrt(MAX / 3) + 1;
	x = 1;
	y = 0;

	while (x < xUpper) {
		index = 1;
		k1 = 3 * x * x;
		y = 2;
		while (1) {
			k = k1 + y * y;
			if (k >= MAX) {
				break;
			}
			toggleBit(k);
			y += sequence[(++index & 1)];
		}
		x += 2;
	}
	xUpper = (long)sqrt(MAX);
	x = 1;
	y = 0;

	while (x < xUpper) {
		k1 = 3 * x * x;
		if ((x & 1) == 0) {
			y = 1;
			index = 0;
		} else {
			y = 2;
			index = 1;
		}
		while (y < x) {
			k = k1 - y * y;
			if (k < MAX) {
				toggleBit(k);
			}
			y += sequence[(++index & 1)];
		}
		x++;
	}
	long n;
	setBit(2);
	setBit(3);
	for ( n = 5; n <= SQRT_MAX; n += 2) {
		if (getBit(n)) {
			int n2 = n * n;
			for (k = n2; k < MAX; k += (2 * n2)) {
				unSetBit(k);
			}
		}
	}
	
	primes[0]=2;
	pn=1;
	for(n=3;n<=MAX;n+=2){
		if(getBit(n)){
			primes[pn++]=n;
		}
	}
	
	
	int i;
	ll inp;
	while(scanf("%lld",&inp)==1){
		factor(2*inp);
		ll res=1;
		for(i=0;i<cn;++i){
			//printf("%lld %d\n",fnx[i],fnx[i]);
			if(fnx[i]&1) res*=cnx[i]+1;
		}
		printf("%lld\n",res);
	}
	return 0;
}
