#include <stdio.h>
extern int a1;
int a();
int b();
static int i = 1;
int c()
{
	i++;
	static int j=2;
	return 0;
}
int main()
{
	printf("a1=%d", a1);
	a();
	b();
	printf("%d\n", i);
	c();
	printf("%d\n", i);
	int j;
	printf("j=%d\n",j);
	return 0;
}
