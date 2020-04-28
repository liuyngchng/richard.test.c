#include <iostream>
#include <stdio.h>
#define BUF_SIZE 1500

using namespace std;

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
	
	int sum_l = 0;
	int l = 0;
	char buf[BUF_SIZE] = {0};
	while (!feof(fp_s)) {
		l = fread(buf, sizeof(char), sizeof(buf), fp_s);
		sum_l +=l;
		fwrite(buf, sizeof(char), l, fp_t);
	}
	cout << sum_l << endl;
	fclose(fp_s);
	fclose(fp_t);
}
