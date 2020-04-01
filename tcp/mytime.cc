/**
  g++ -fPIC -shared mytime.cc -o libmytime.so
**/
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
using namespace std;

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
   char* time = get_time();
    time[strlen(time)-1]=0;
   cout << "the calendar time now is " << time << endl;
   cout << "output " << get_time() << endl;
}
