#include <stdio.h>
int main(){
    char s[256];
    char *p;
    unsigned long long int h = 0;
     
    scanf("%s", s);
    for(p=s; *p; p++){
        h = h*31 + *p;
    }
    printf("%llu\r\n", h);
}

