# include<string.h>
# include<stdio.h>
int main()
{
    char c[10];
    memset(c,0,sizeof(c));
    int a = strlen(c);
    int b = sizeof(c);
    printf("strlen(c)=%d, sizeof(c)=%d\n",a,b);
    c[0]='\000';
    c[1]='\000';
    a = strlen(c);
    b = sizeof(c);
    printf("strlen(c)=%d, sizeof(c)=%d\n",a,b);
    c[0]='\000';
    c[1]='a';
    a = strlen(c);
    b = sizeof(c);
    printf("strlen(c)=%d, sizeof(c)=%d\n",a,b);
    c[0]='a';
    c[1]='b';
    c[2]='\000';
    a = strlen(c);
    b = sizeof(c);
    printf("strlen(c)=%d, sizeof(c)=%d\n",a,b);
}
