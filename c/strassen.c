#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

typedef long long ll;
typedef struct{
	ll **a;
	int m,n;
}matrix;

void read(matrix *a){
	scanf("%d%d",&(a->m),&(a->n));
	int i,j;
	a->a=(ll**) malloc(sizeof(ll*)*a->m);
	for(j=0;j<a->m;++j){
		a->a[j]=(ll*) malloc(sizeof(ll)*a->n);
		for(i=0;i<a->n;++i){
			scanf("%lld",a->a[j]+i);
		}
	}
}

void show(matrix *a){
	int j,i;
	printf("----  %d x %d ----\n",a->m,a->n);
	for(j=0;j<a->m;++j){
		
		for(i=0;i<a->n;++i){
			printf("%5lld ",a->a[j][i]);
		}
		printf("\n");
	}
}

void release(matrix *a){
	int i;
	for(i=0;i<a->m;++i) free(a->a[i]);
	free(a->a);
}

void straight(matrix *a,matrix *b, matrix *c){
	int j,i,k;
	assert(a->n==b->m);
	c->m=a->m;
	c->n=b->n;
	c->a=(ll**) malloc(sizeof(ll*)*c->m);
	ll sum;
	for(j=0;j<a->m;++j){
		c->a[j]=(ll*) malloc(sizeof(ll)*c->n);
		for(i=0;i<b->n;++i){
			sum=0;
			for(k=0;k<a->n;++k){
				sum+=a->a[j][k] * b->a[k][i];
			}
			c->a[j][i]=sum;
		}
	}
}

void add(matrix *a,matrix *b,matrix *c){
	assert(a->m==b->m &&a->n==b->n);
	int i,j;
	c->m=a->m;
	c->n=a->n;
	c->a=(ll**) malloc(sizeof(ll*)*c->m);
	for(j=0;j<c->m;++j){
		c->a[j]=(ll*) malloc(sizeof(ll)*c->n);
		for(i=0;i<c->n;++i){
			c->a[j][i]=a->a[j][i]+b->a[j][i];
		}
	}
}

void sub(matrix *a,matrix *b,matrix *c){
	assert(a->m==b->m &&a->n==b->n);
	int i,j;
	c->m=a->m;
	c->n=a->n;
	c->a=(ll**) malloc(sizeof(ll*)*c->m);
	for(j=0;j<c->m;++j){
		c->a[j]=(ll*) malloc(sizeof(ll)*c->n);
		for(i=0;i<c->n;++i){
			c->a[j][i]=a->a[j][i]-b->a[j][i];
		}
	}
}

void copy(matrix *dst,matrix *src,int j1,int j2,int i1,int i2){
	// [j1 -> j2)
	int i,j;
	dst->m=j2-j1;
	dst->n=i2-i1;
	dst->a=(ll**) malloc(sizeof(ll*)*dst->m);
	for(j=0;j<dst->m;++j){
		dst->a[j]=(ll*) malloc(sizeof(ll)*dst->n);
		for(i=0;i<dst->n;++i){
			dst->a[j][i]=src->a[j+j1][i+i1];
		}
	}
}

void split(matrix *A,matrix *a11,matrix *a12,matrix *a21,matrix *a22){
	int k=A->n/2;
	copy(a11,A,0,k,0,k);
	copy(a12,A,0,k,k,A->n);
	copy(a21,A,k,A->n,0,k);
	copy(a22,A,k,A->n,k,A->n);
}
void merge(matrix *A,matrix *a11,matrix *a12,matrix *a21,matrix *a22){
	int j,i;
	A->m=a11->m+a21->m;
	A->n=a11->n+a12->n;
	A->a=(ll**) malloc(sizeof(ll*)*A->m);
	for(j=0;j<A->m;++j){
		A->a[j]=(ll*) malloc(sizeof(ll)*A->n);
	}
	for(j=0;j<a11->m;++j){
		for(i=0;i<a11->n;++i){
			A->a[j][i]=a11->a[j][i];
		}
	}
	for(j=0;j<a12->m;++j){
		for(i=0;i<a12->n;++i){
			A->a[j][a11->n+i]=a12->a[j][i];
		}
	}
	for(j=0;j<a21->m;++j){
		for(i=0;i<a21->n;++i){
			A->a[a11->m+j][i]=a21->a[j][i];
		}
	}
	for(j=0;j<a22->m;++j){
		for(i=0;i<a22->n;++i){
			A->a[a11->m+j][a11->n+i]=a22->a[j][i];
		}
	}
}
void strassen(matrix *a,matrix *b,matrix *c){

	if(a->n<128){
	/*
		c->m=a->m;
		c->n=a->n;
		c->a=(ll**) malloc(sizeof(ll*));
		c->a[0]=(ll*)malloc(sizeof(ll));
		c->a[0][0]=a->a[0][0] * b->a[0][0];
	*/
		straight(a,b,c);
		return ;
	}
	matrix a11,a12,a21,a22,b11,b12,b21,b22;
	split(a,&a11,&a12,&a21,&a22);
	split(b,&b11,&b12,&b21,&b22);
	matrix p1,p2,p3,p4,p5,p6,p7;
	matrix t1,t2;
	// p1 =(a11+a22) *(b11+b22)
	add(&a11,&a22,&t1);
	add(&b11,&b22,&t2);
	strassen(&t1,&t2,&p1);
	release(&t1);
	release(&t2);
	
	// p2 =(a21+a22)*b11
	add(&a21,&a22,&t1);
	strassen(&t1,&b11,&p2);
	release(&t1);
	// p3 = a11 *(b12+b22)
	sub(&b12,&b22,&t1);
	strassen(&a11,&t1,&p3);
	release(&t1);
	//p4 = a22 *(b21+b11)
	sub(&b21,&b11,&t1);
	strassen(&a22,&t1,&p4);
	release(&t1);
	//p5 = (a11+a12) *b22
	add(&a11,&a12,&t1);
	strassen(&t1,&b22,&p5);
	release(&t1);
	//p6 = 
	sub(&a21,&a11,&t1);
	add(&b11,&b12,&t2);
	strassen(&t1,&t2,&p6);
	release(&t1);
	release(&t2);
	//p7
	sub(&a12,&a22,&t1);
	add(&b21,&b22,&t2);
	strassen(&t1,&t2,&p7);
	release(&t1);
	release(&t2);
	///////////////
	release(&a11);
	release(&a12);
	release(&a21);
	release(&a22);
	release(&b11);
	release(&b12);
	release(&b21);
	release(&b22);
	/****************************************/
	matrix c11,c12,c21,c22;
	// c11= p1+p4 +( p7-p5)
	add(&p1,&p4,&t1);
	sub(&p7,&p5,&t2);
	add(&t1,&t2,&c11);
	release(&t1);
	release(&t2);
	// c12=p3+p5
	add(&p3,&p5,&c12);
	// c21=p2+p4
	add(&p2,&p4,&c21);
	//c22 = p1+p3 +(p6-p2)
	add(&p1,&p3,&t1);
	sub(&p6,&p2,&t2);
	add(&t1,&t2,&c22);
	release(&t1);
	release(&t2);
	merge(c,&c11,&c12,&c21,&c22);
	release(&p1);
	release(&p2);
	release(&p3);
	release(&p4);
	release(&p5);
	release(&p6);
	release(&p7);
	release(&c11);
	release(&c12);
	release(&c21);
	release(&c22);
}
#define max2(a,b) ((a)>(b)?(a):(b))
void mul( matrix *a,matrix *b,matrix *c){
	matrix ta,tb,tc;
	assert(a->n==b->m);
	int n=1,m=max2(max2(a->m,a->n),max2(b->m,b->n));
	int i,j;
	while(n<m){
		n<<=1;
	}
	ta.m=n;
	ta.n=n;
	tb.m=n;
	tb.n=n;
	ta.a=(ll**)malloc(sizeof(ll*)*n);
	for(j=0;j<n;++j){
		ta.a[j]=(ll*)malloc(sizeof(ll)*n);
	}
	tb.a=(ll**)malloc(sizeof(ll*)*n);
	for(j=0;j<n;++j){
		tb.a[j]=(ll*)malloc(sizeof(ll)*n);
	}
	for(j=0;j<n;++j){
		for(i=0;i<n;++i){
			if(j<a->m && i<a->n){
				ta.a[j][i]=a->a[j][i];
			}else{
				ta.a[j][i]=0;
			}
			if(j<b->m && i<b->n){
				tb.a[j][i]=b->a[j][i];
			}else{
				tb.a[j][i]=0;
			}
		}
	}
	//show(&ta);
	//show(&tb);
	strassen(&ta,&tb,&tc);
	//show(&tc);
	c->m=a->m;
	c->n=b->n;
	c->a=(ll**)malloc(sizeof(ll*)*c->m);
	for(j=0;j<c->m;++j){
		c->a[j]=(ll*)malloc(sizeof(ll)*c->n);
		for(i=0;i<c->n;++i){
			c->a[j][i]=tc.a[j][i];
		}
	}
	release(&ta);
	release(&tb);
	release(&tc);
}
void rand_matrix(matrix *a,int m,int n){
	a->m=m;
	a->n=n;
	a->a=(ll**) malloc(sizeof(ll*)*a->m);
	int j,i;
	for(j=0;j<a->m;++j){
		a->a[j]=(ll*) malloc(sizeof(ll)*a->n);
		for(i=0;i<a->n;++i){
			a->a[j][i]=rand()%4;	
		}
	}
}
int main(void) {
	srand(time(NULL));
	matrix a,b,c;
	rand_matrix(&a,512,512);
	rand_matrix(&b,512,512);
    mul(&a,&b,&c);
	/*
	matrix d;
	straight(&a,&b,&d);
	int j,i;
	for(j=0;j<c.m;++j){
		for(i=0;i<c.n;++i){
			assert(c.a[j][i]==d.a[j][i]);
		}
	}*/
	return 0;
}
