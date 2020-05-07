#include <iostream>
#include <stdio.h>
#include <string.h>
#include "trans.h"
#include <iomanip>

#ifndef BUF_SIZE
#define BUF_SIZE 1500
#endif

using namespace std;

void get_file_name(const char path[], char name[])
{
    //cout << "path=" << path << endl;
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
	char file_path_s[] = "/home/rd/workspace/richard.test.c/tcp/file_srv/client.o";
	char file_path_t[] = "./_write_test";
	FILE* fp_s;
	if ((fp_s = fopen(file_path_s,"rb")) == NULL) {
    	cout << "can't open source file " << file_path_s << endl;;
    	return -1;
    }

	FILE* fp_t;
	if((fp_t = fopen(file_path_t, "wb")) == NULL) {
		cout << "can't open target file " << file_path_t << endl;
		return -1;
	}
	
	fseek(fp_s, 0, SEEK_END);
	long pos = ftell(fp_s);
	cout << "source_file_size=" << pos << "; source_file=" << file_path_s << endl;	
	rewind(fp_s);
	int len =100;
	float f = (float)len / pos * 100;
	cout << "percent is " << fixed << setprecision(2) << f << "%" << endl; 
	len	= 196915200;
	len /= 1024 * 1024;
	pos = 1996488704;
	pos /= 1024 * 1024;
	cout << "percent in MB " << len << "MB/" << pos << endl << "MB";
	int sum_l = 0;
	int l = 0;
	char buf[BUF_SIZE] = {0};
	while (!feof(fp_s)) {
		l = fread(buf, sizeof(char), sizeof(buf), fp_s);
		sum_l +=l;
		fwrite(buf, sizeof(char), l, fp_t);
	}
	cout << "read_length=" << sum_l << endl;
	fseek(fp_t, 0, SEEK_END);
    pos = ftell(fp_t);
    cout << "target_file_size=" << pos << "; target_file=" << file_path_t << endl;
    rewind(fp_t);
	fclose(fp_s);
	fclose(fp_t);
	char b[strlen(file_path_s) + 1] = {0};
	bzero(b, sizeof(b));
	cout << "path=" << file_path_s << endl;
	get_file_name(file_path_s, b);
	cout << "name=" << b << endl;

}
