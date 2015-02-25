#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

typedef long long ll;

typedef struct {
	int key,val;
} item;

#define base_size 2
#define ASSERT(x) assert(x)
#define TYPE item
#define CMP(a,b) ((a).key<(b).key?-1:(a).key>(b).key?1:0)
typedef struct heap{
	TYPE *a;
	int alloc_size;
	int n;
}heap;

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
	/*(x)->a[(x)->n-1]=(e);*/											\
}while(0)

#define POP(x) do{													\
	if((x)->alloc_size>base_size && (x)->n<((x)->alloc_size>>2)){ 		\
		(x)->alloc_size>>=2; 										\
		(x)->a=(TYPE*) realloc((x)->a,(x)->alloc_size*sizeof(TYPE)); 	\
		ASSERT((x)->a); 												\
	} 																\
	(x)->n--; 														\
}while(0)

#define RELEASE(h) if((h)->a) free((h)->a)

#ifndef CMP
#error "must define CMP"
#endif

void heap_push(heap *h, TYPE value){
	int index,parent;
	PUSH(h,value);
	for(index=h->n-1;index;index=parent){
		parent=(index-1)>>1;
		if(CMP(h->a[parent],value)<=0) break;
		h->a[index]=h->a[parent];
	}
	h->a[index]=value;
}

void heap_pop(heap *h){
	TYPE tmp=h->a[h->n-1];
	POP(h);
	int index,first,second;
	for(index=0;; index=first){
		first=(index<<1)+1;
		if(first>=h->n) break;
		second=first+1;
		if(second < h->n && CMP(h->a[second],h->a[first])<0) first=second;
		if(CMP(tmp,h->a[first])<=0) break;
		h->a[index]=h->a[first];
	}
	h->a[index]=tmp;
}
int main(void) {
	heap h;
	INIT(&h);
	srand(time(NULL));
	int i,n=10;
	for(i=0;i<n;++i){
		item a;
		a.key=rand()%10;
		a.val=i;
		heap_push(&h,a);
	}
	while(h.n){
		printf("%d %d\n",h.a[0].key,h.a[0].val);
		heap_pop(&h);
	}
	RELEASE(&h);
	return 0;
}
