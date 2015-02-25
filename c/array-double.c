#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef long long ll;

#define ASSERT assert
#define TYPE ll
#define base_size 2

typedef struct num{
	ll *a;
	int sign;
	int alloc_size;
	int n;
}num;

#define INIT(x) do{													\
	(x)->a=(TYPE*) malloc(sizeof(TYPE)*base_size); 					\
	(x)->alloc_size=base_size; 										\
	(x)->n=0;														\
}while(0)

#define PUSH(x, e) do{  											\
	if((x)->n==(x)->alloc_size) {										\
		(x)->alloc_size<<=1;											\
		(x)->a=(TYPE*) realloc((x)->a,(x)->alloc_size*sizeof(TYPE));	\
		ASSERT((x)->a);												\
	}																\
	(x)->n++; 														\
	(x)->a[(x)->n-1]=(e);											\
}while(0)

#define POP(x) do{													\
	if((x)->alloc_size>base_size && (x)->n<((x)->alloc_size>>2)){ 		\
		(x)->alloc_size>>=2; 										\
		(x)->a=(TYPE*) realloc((x)->a,(x)->alloc_size*sizeof(TYPE)); 	\
		ASSERT((x)->a); 												\
	} 																\
	(x)->n--; 														\
}while(0)

#define RELEASE(h) free((h)->a)
void print(const num *x){
	int i;
	printf("%d\n",x->n);
	for(i=0;i< x->n;++i){
		printf("%lld",x->a[i]);
	}
}

int main(void) {
	num *a;
	a=malloc(sizeof(num));
	INIT(a);
	PUSH(a,1);
	PUSH(a,3);
	PUSH(a,1);
	PUSH(a,3);
	PUSH(a,1);
	PUSH(a,3);
	POP(a);
	POP(a);
	POP(a);
	POP(a);
	

	print(a);
	RELEASE(a);
	return 0;
}
