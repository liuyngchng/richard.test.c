/**
** gcc -fPIC -shared time.c -o libtime.so
**/
# include <time.h>
# include <string.h>
# include <stdio.h> 
char* get_time()
{
    struct tm *ptr; 
    time_t lt;
    lt =time(NULL);
    ptr = localtime(&lt);
    char* t = asctime(ptr);
    t[strlen(t)-1]=0;
    return t;
}

int main()
{
   char * time = get_time();
    time[strlen(time)-1]=0;
   printf("The Calendar Time now is [%s]/n", time);
        
}
