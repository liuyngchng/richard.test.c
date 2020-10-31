#include <stdio.h>

char a[] = "this is from say";

static int c = 10;

void say()
{
	printf("msg=%s\n", a);
}

int fun()
{
    static int count = 10; 
    return count--;
}

int ct()
{
	return c--;	
}
