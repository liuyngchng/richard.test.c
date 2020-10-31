#include <stdio.h>

static char a[] = "this is from main";

void say();
int fun();

int ct();

int main()
{
	say();
	for(int count = 0; count < 10; count++) {
		printf("%d -- %d -- %d\n", count, fun(), ct());
	}
}
