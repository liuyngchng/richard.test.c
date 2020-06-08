#include<stdio.h>
#include<math.h>
#include<string.h>
void say(int test1, int test2);
void say_hello(int m, int n);
int main()
{
    long int i,x,y;
    for(i=1;i<100000;i++)
    {
        x=sqrt(i+100);
        y=sqrt(i+268);
        if(x*x==i+100&&y*y==i+268)
        {
            printf("\n%ld\n",i);
        }
    }
    int a=10;
    char *b="this is a test";
    say(11, 20);
    printf("done,%s\r\n", b);
}

void say(int test1, int test2)
{
    int a=11;
    char *b="this is another test";
    printf("hello, this is me,%d!\r\n", test1);
    say_hello(a, test2);
}
void say_hello(int m, int n)
{
    printf("hello, world, %d, %d\r\n", m, n);
}

