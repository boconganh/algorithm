#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define __sort
#define type void*
typedef int (*_sort_cmp_fn_t)(const type,const type);

inline type _sort_max(type a,type b,_sort_cmp_fn_t cmp){
	if(cmp(a,b)>0) return a;
	return b;
}
inline type _sort_min(type a,type b,_sort_cmp_fn_t cmp){
	if(cmp(a,b)<0) return a;
	return b;
}
inline void _sort_swap(type a,type b,int size){
	if(size>16){
		type t=malloc(size);
		assert(t!=0);
		memcpy(t,a,size);
		memcpy(a,b,size);
		memcpy(b,t,size);
		free(t);
	}else{
		char tmp[size];
		memcpy(tmp,a,size);
		memcpy(a,b,size);
		memcpy(b,tmp,size);
	}
}

#define A(i) ((a)+(i)*(size))

inline int binary_insert_sort_find(const type x,type a,const int n,
		int size,_sort_cmp_fn_t cmp){
	int l,r,c;
	type cx;
	l=0;
	r=n-1;
	c=r>>1;
	if(cmp(x,A(0))<0){
		return 0;
	}else if(cmp(x,A(r))>0){
		return r;
	}
	cx=A(c);
	while(1){
		const int val=cmp(x,cx);
		if(val<0){
			if(c-l<=1) return c;
			r=c;
		}else{
			if(r-c<=1) return c+1;
			l=c;
		}
		c=l+((r-l)>>1);
		cx=A(c);
	}
}

inline void binary_insert_sort_start(type a,const int start,const int n,
		_sort_cmp_fn_t cmp,int size){
	register int i,j,location;
	type x=malloc(size);
	assert(x!=0);
	for(i=start;i<n;++i){
		if(cmp(A(i-1),A(i))<=0) continue;
		memcpy(x,A(i),size);
		location=binary_insert_sort_find(x,a,i,size,cmp);
		for(j=i-1;j>=location;--j){
			memcpy(A(j+1),A(j),size);
		}
		memcpy(A(location),x,size);
	}
	free(x);
}

inline void binary_insert_sort(type a,const int n, int size,_sort_cmp_fn_t cmp){
	if(n<=1) return;
	binary_insert_sort_start(a,1,n,cmp,size);
}

inline void merge_sort(type a,const int n,int size,_sort_cmp_fn_t cmp){
    if(n<16){
        binary_insert_sort(a,n,size,cmp);
        return;
    }
    int mid=n>>1;
    type newa=malloc(size*n);
    merge_sort(a,mid,size,cmp);
    merge_sort(A(mid),n-mid,size,cmp);
    register int i=0,j=mid,out=0;
    while(out<n){
        if(i<mid){
            if(j<n){
                if(cmp(A(i),A(j))<=0){
                    memcpy(newa+out*size,A(i),size);
                    i++;
                }else{
                    memcpy(newa+out*size,A(j),size);
                    j++;
                }
            }else{
                memcpy(newa+out*size,A(i),size);
                i++;
            }
        }else{
            memcpy(newa+out*size,A(j),size);
            j++;
        }
        out++;
    }
    memcpy(a,newa,size*n);
    free(newa);
}
inline void random_quick_sort_with_range(type a,int size,
		_sort_cmp_fn_t cmp,int p,int q){
	if(q-p<=16){
		binary_insert_sort(A(p),q-p+1,size,cmp);
		return;
	}
	int m=rand()%(q-p+1);
	_sort_swap(A(q),A(p+m),size);
	register int j,r=p-1;
	for(j=p;j<q;j++){
		if(rand()%2){
			if(cmp(A(j),A(q))<=0){
				_sort_swap(A(++r),A(j),size);
			}
		}else{
			if(cmp(A(j),A(q))<0){
				_sort_swap(A(++r),A(j),size);
			}
		}
	}
	_sort_swap(A(++r),A(q),size);
	random_quick_sort_with_range(a,size,cmp,p,r-1);
	random_quick_sort_with_range(a,size,cmp,r+1,q);
}
inline void random_quick_sort(type a,int n,int size,_sort_cmp_fn_t cmp){
	srand(time(NULL));
	random_quick_sort_with_range(a,size,cmp,0,n-1);
}

inline void heap_sift_down(type a,int size,
		_sort_cmp_fn_t cmp,int start,int end){
	register int child,root=start;
	while((root<<1)<=end){
		child=root<<1;
		if(child<end && cmp(A(child),A(child+1))<0){
			child++;
		}
		if(cmp(A(root),A(child))<0){
			_sort_swap(A(root),A(child),size);
			root=child;
		}else return;
	}
}
inline void heapify(type a,int size,_sort_cmp_fn_t cmp,int n){
	register int start=n>>1;
	while(start>=0){
		heap_sift_down(a,size,cmp,start,n-1);
		start--;
	}
}
inline void heap_sort(type a, int n,int size,_sort_cmp_fn_t cmp){
	register int end;
	if(n<2) return;
	end=n-1;
	heapify(a,size,cmp,n);
	while(end>0){
		_sort_swap(A(end),a,size);
		heap_sift_down(a,size,cmp,0,end-1);
		end--;
	}
}
#undef A
#undef type
#undef __sort

int cmplong(const void *a,const void *b){
    return *(long*)a-*(long*)b;
}

#define maxn 100100
long odd[maxn],even[maxn];
int nodd,neven;
int main(){
        long a[]={18,2,2015,1,1,2015};
	int n=6;
	int i;
             random_quick_sort(a,n,sizeof(long),cmplong);
	for(i=0;i<n;++i){
		printf("%ld\n",a[i]);
	}
	
	return 0;
}
