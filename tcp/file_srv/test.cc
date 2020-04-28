#include <string.h>
#include <iostream>

#include "common.h"

//using namespace std;

void get_file_name(char path[], char name[]);

int main(int argc, char* argv[])
{
	char a[] = "/home/rd/workspace/richard.test.c/tcp/file_srv/server.o";
	char* b = new char[strlen(a)+1];
	cout << "path=" << a << endl;
	get_file_name(a,b);
	cout << "name=" << b << endl;
	return 0;
}
