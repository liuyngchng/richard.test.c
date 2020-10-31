#include <stdio.h>

void do_throw()
{
	throw -1;
}

int try_throw()
{
	try {
		do_throw();
	} catch (int e) {
		printf("%d catched\n", e);
		return -1; 
	}
	return 0;
}

int main()
{
	try_throw();
}
