#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

void get_file_name(char path[], char name[])
{
	int j = strlen(path)-1;
	int i = j; 
    for ( ; i >= 0 ; i--) {
        if (path[i] == '/' || path[i] == '\\') 
            break;
        else
            name[j-i] = path[i];
    }
	//cout << "temp=" << name << endl;
	j = strlen(name)-1;
	for (i = 0; i <= j/2; i++) {
		char temp = name[i];
		name[i] = name[j-i];
		name[j-i] = temp;
	}
	name[j+2] = '\0';
    cout << "get_file_name="<< name << endl;
}


int main(int argc, char* argv[])
{
	char a[] = "./server.o";
	char* b = new char[strlen(a)+1];
	cout << "path=" << a << endl;
	get_file_name(a,b);
	cout << "name=" << b << endl;
	return 0;
}
