#include <stdio.h>
#define max(x,y) ({ \
typeof(x) _max1= (x);\
typeof(y) _max2= (y);\
(void)(&_max1==&_max2);\
_max1>_max2?_max1:_max2;})

#define getint() ({ int __tmp; scanf("%d",&__tmp); __tmp;})
int main(void) {
	
	printf("%d\n", max(1,2));
	int a=getint();
	printf("%d\n",a);
	return 0;
}
