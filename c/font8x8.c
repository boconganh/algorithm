#include <stdio.h>

/*
  **    
 ****   
**  **  
**  **  
******  
**  **  
**  ** 

******  
 **  ** 
 **  ** 
 *****  
 **  ** 
 **  ** 
****** 

*/
char font[][8]={
	{
	0b001100,
	0b011110,
	0b110011,
	0b110011,
	0b111111,
	0b110011,
	0b110011
	},
	{
	0b111110,
	0b011011,
	0b011011,
	0b011110,
	0b011011,
	0b011011,
	0b111110
	}
};

void print_font(char *bitmap){
	int i,j;
	for(j=0;j<8;++j){
		for(i=7;i>=0;--i){
			putchar((bitmap[j]&(1<<i))?'*':' ' );
		}
		printf("\n");
	}
}
void first_char(char* ten){
	int i=0;
	while(!isalpha(ten[i]))i++;
	print_font(font[ten[i]-'A']);
}
int main(void) {
	char ten[100];
	int n=100;
	fgets(ten,n,stdin);
	first_char(ten);
	return 0;
}
