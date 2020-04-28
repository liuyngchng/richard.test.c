#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<string>
#include<iostream>
#include<fstream>
#include"common.h"

#define _PORT_ 	8080							//server port
#define _IP_ 	"127.0.0.1"						//server IP
#define _PATH_ 	"/home/rd/test/cli/"			//client download defalt path

using namespace std;

// get file name from full path.
void get_file_name(const char full_path[], char file_name[]);

// write file stream named file(file full path) to sockfd 
int snd_f(const char file[], int sockfd); 

// read file stream from sockfd sockfd and write to file named file
int save_f(const char file[], int sockfd); 

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
	
	char cmd[CMD_SIZE]={0}, file[FILE_SIZE]={0}, file_name[FILE_SIZE]={0};
	cout << "input your cmd:" << endl;
	cin >> cmd >> file;
 	cout <<"cmd=" << cmd << ";file=" << file << endl; 
	snd_buf(sockfd, cmd, CMD_SIZE); 					//send cmd to server
	if (strcmp(cmd, "put") == 0) {
		get_file_name(file, file_name);
		snd_buf(sockfd, file_name, FILE_SIZE);				//send file name to server
		if (snd_f(file, sockfd) == 0)
			cout <<"upload successfully" << endl;	
	} else if (strcmp(cmd, "get") == 0) {		//download a file from server	
		snd_buf(sockfd, file, FILE_SIZE);				//send file name to server
		string path = _PATH_;
		path += file;
		const char *p = path.c_str();
		if (save_f(p, sockfd) == 0) {
			cout << "download successfully" << endl;
		} 
	} else {
		cout << "illegal operation" << endl;
	}

	close(sockfd);
	return 0;
}
