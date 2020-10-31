#include <ctype.h>
#include <stdio.h>

void itoa(int n,char s[])
{
    int i, j, sign;
    if ((sign=n) < 0)
        n=-n;
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    }
    while ((n /= 10) > 0);
    if (sign < 0)
        s[i++]='-';
    s[i]='\0';
    for (j = i; j >= 0; j--)
        printf("%c",s[j]);
}

int main()
{
    int n = 1234567;
    char s[100];
    itoa(n ,s);
}
