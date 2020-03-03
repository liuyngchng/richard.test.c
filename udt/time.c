/**
** gcc -fPIC -shared time.c -o libtime.so
**/
# include <time.h>
# include <stdio.h> 
char* get_time()
{
    struct tm *ptr; 
    time_t lt;
    lt =time(NULL);
    ptr = localtime(&lt);
    return asctime(ptr);  
}

int main()
{
   char * time = get_time();     
   printf("The Calendar Time now is %s/n", time);
        
}
