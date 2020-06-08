#include <stdio.h>
//#include <sys/types>
 
int main()
{
	int x=0x12345678; /* 305419896 */
	unsigned char *p=(char*)&x;
	printf("%0x % 0x %0x %0x",p[0],p[1],p[2],p[3]);
	return 0;
} 
