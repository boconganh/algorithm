#include <stdio.h>
#include <string.h>


void reverse(char *s){
	int i,n=strlen(s);
	for(i=0;i<n/2;++i){
		int t=s[i];
		s[i]=s[n-i-1];
		s[n-i-1]=t;
	}
}
void read(char *s){
	scanf("%s",s);
	// so A=a0*10^n+...an
	reverse(s);
	//=> A=an+... a0*10^n
}
void divmod(char *a,int d,int *r){ 
	/*
	  a = a div d
	  *r= a mod d
	*/
	int n=strlen(a);
	int i=n-1;
	long t=0;
	while(i>=0){
		t=t*10+(a[i]-'0');
		a[i]=(t/d)+'0';
		t%=d;
		i--;
	}
	i=n-1;
	
	// xoa so 0 khong co nghia o dau cua phep chia
	while(i>=0 && a[i]=='0'){
		a[i]=0;
		i--;
	}
	*r=t;
}

int main(void) {
	char s[10000];
	read(s);
	int b;
	scanf("%d",&b);
	char out[10000];
	const char *t="0123456789ABCDEF";
	int r,len=0;
	while(strlen(s)){
		divmod(s,b,&r);
		out[len++]=t[r];
	}
	out[len]=0;
	reverse(out);
	puts(out);
	return 0;
}
