#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <string>
#include <iostream>
#include <fstream>
#include "trans.h"

#define _PORT_ 	8080							//server port
#define _IP_ 	"127.0.0.1"						//server IP
#define _PATH_ 	"/home/rd/test/cli/"			//client download defalt path

using namespace std;

// get file name from full path.
void get_file_name(const char path[], char file_name[]);

// write file stream named file(file full path) to sockfd 
int snd_f(const char path[], int sockfd); 

// read file stream from sockfd sockfd and write to file named file
int save_f(const char path[], const int size, int sockfd); 

int main(int argc, char** argv){
	int cLen = 0;
	struct sockaddr_in sock_addr;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(_PORT_);
	inet_pton(AF_INET, _IP_, &sock_addr.sin_addr);
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		cout << "socket fail" << endl;
		return -1;
	}
	if (connect(sockfd, (struct sockaddr*)&sock_addr, sizeof(sock_addr)) < 0) {
		cout << "connect error" << endl;
		return -1;
	}
	
	char cmd[CMD_SIZE] = {0}, file[FILE_SIZE] = {0}, file_name[FILE_SIZE] = {0}, file_size[FILE_SIZE] = {0};
	cout << "input your cmd:" << endl;
	cin >> cmd >> file;
 	cout <<"cmd = " << cmd << ";file = " << file << endl; 
	snd_buf(sockfd, cmd, CMD_SIZE); 						//send cmd to server
	int i_f_size = 0;
	if (strcmp(cmd, "put") == 0) {
		get_file_name(file, file_name);
		snd_buf(sockfd, file_name, FILE_SIZE);				//send file name to server
		cout << "sent file_name " << file_name << endl;
		i_f_size = get_file_size(file);
		itoa(i_f_size, file_size);
		cout << "file_size_str=" << file_size << endl;
		snd_buf(sockfd, file_size, FILE_SIZE); 
		cout << "sending " << file_name << endl;
		if (snd_f(file, sockfd) == 0)
			cout <<"upload success." << endl;	
	} else if (strcmp(cmd, "get") == 0) {					//download a file from server	
		snd_buf(sockfd, file, FILE_SIZE);					//send file name to server
		string path = _PATH_;
		path += file;
		const char *p = path.c_str();
		//cout << "downloading " << p << endl;
		rcv_buf(sockfd, file_size, FILE_SIZE);        		//receive file size
		cout << "file_size_str=" << file_size << endl;
		i_f_size = atoi(file_size);
		if (save_f(p, i_f_size, sockfd) == 0) {
			cout << "download success." << endl;
		} 
	} else {
		cout << "illegal operation" << endl;
	}

	close(sockfd);
	return 0;
}
