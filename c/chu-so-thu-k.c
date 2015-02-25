#include <stdio.h>
long pow(long n,long k){
	if(k==0) return 1;
	long t=pow(n,k/2);
	if(k%2==0){
		return t*t;
	}else{
		return t*t*n;
	}
}

long dem(long i){
	//dem tat ca cac so co i chu so
	return 9*pow(10,i-1);
}

char kth(long k){
	long d=0;
	long i=1;
	while(d+dem(i)*i < k){
		// neu tat ca cac so co i chu so van nho hon k
		// tang bien d len
	 	d+=dem(i)*i;
	 	i++;
	}
	long start=d+1; // vi tri dau tien cua so co i chu so
	long t=(k-start)/i; // t thu tu cua so co i chu so trong day can tim
	long nth=t+pow(10,i-1); // thu tu cua so can tim
	long ind=(k-start) %i; // ind la chi so cua ki tu  can tim  trong nth
	char s[30];
	sprintf(s,"%ld",nth);
	return s[ind];
}

int main() {
	long i;
	putchar(kth(1000));
	return 0;
}
