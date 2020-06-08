#include "md5.h"
#include <fstream>
#include <iostream>

using namespace std;

/* Prints a message digest in hexadecimal.
 */
static void md5_print (md5_byte_t digest[16])
{
	for (int i = 0; i < 16; i++)
		printf ("%02x", digest[i]);
	printf("\n");
}

int main(int argc, char* argv[])
{
	if(argc < 2) {
		cout << "pls input file name" << endl;
	}
	md5_state_t ms;
	md5_init(&ms);
	FILE *file;
	char *filename = argv[1]; //[] = "../server.cc";
	if ((file = fopen (filename, "rb")) == NULL) {
		cout << filename << "can't be opened" << endl;
		return -1;
	}
	md5_byte_t buffer[1024] = {0}, digest[16] = {0};
	int len = 0;
	while (len = fread (buffer, 1, 1024, file))
		md5_append(&ms, buffer, len);
	md5_finish(&ms, digest);   	
	md5_print(digest);	
	return 0;

}
