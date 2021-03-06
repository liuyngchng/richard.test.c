/**
 * a file server, user need to input command like
 * download test.txt or upload test.txt
 */
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
#include <fstream>
#include <iostream>
#include "trans.h"
//#define _PORT_ 8080					    //default listing port
#define _BACL_LOG_ 10
#define _PATH_ "./"						//file path for server

using namespace std;

// declaration.
int save_f(const char path[], const int size, int sockfd); //save stream in sockfd to file
int snd_f(const char path[], int sockfd);				//send file content to stream sockfd
void get_file_name(const char path[], char name[]);

int main(int argc, char** argv){
	if (argc < 2) {
        cerr <<"usage: ./cmd port" << endl;
        return 1;
    }
	int sockfd, acceptfd;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		cout << "socket error";
		return -1;
	}
	cout << "create socket ok" << endl;
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(atoi(argv[1]));
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(my_addr.sin_zero), 0);
	if ((bind(sockfd, (struct sockaddr*)&my_addr, 
			sizeof(struct sockaddr))) == -1) {
		cout <<"bind error" << endl;
		return -2;
	}
	cout << "bind socket ok" << endl;

	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, 
		(char*)&my_addr, sizeof(my_addr)); 

	if (listen(sockfd, _BACL_LOG_) == -1) {
		perror("listen error");
		return -3;
	}
	cout << "listen to port " << argv[1] << " ok" << endl;
    cout << "default directory is " << _PATH_ << endl;
	unsigned int sin_size = sizeof(my_addr);
	acceptfd = accept(sockfd, (struct sockaddr*)&my_addr, &sin_size);
	if (acceptfd < 0) {
		close(sockfd);
		cout << "accept failed" << endl;
		return -4;
	}
	cout << "accept ok" << endl;
	
	char cmd[CMD_SIZE] = {0};							//save cmd：get || put 
	char file_name[FILE_SIZE] = {0};					//file_name from client 
	char file_size[FILE_SIZE] = {0};
	rcv_buf(acceptfd, cmd, CMD_SIZE);					//receive cmd
	int i_f_size = 0;									//receive file size
	if (strcmp(cmd, "put") == 0) {
		cout << "cmd is " << cmd << endl;
		rcv_buf(acceptfd, file_name, FILE_SIZE);		//receive file name 
		rcv_buf(acceptfd, file_size, FILE_SIZE);		//receive file size
		cout << "file_size_str=" << file_size << endl;
		i_f_size = atoi(file_size);
		char name[FILE_SIZE] = {0};
		get_file_name(file_name, name); 
		string path = _PATH_;
		path += name;
		const char *p = path.c_str();
		cout << "receiving " << file_name << endl;
		if (save_f(p, i_f_size, acceptfd) == 0)			//receive stream and save to file
			cout <<"saved " << _PATH_ << file_name << endl;
	} else if (strcmp(cmd, "get") == 0) {
		cout <<"cmd is " << cmd << endl;
		rcv_buf(acceptfd, file_name, FILE_SIZE);		//receive file name
		string path = _PATH_;
		path += file_name;
		i_f_size = get_file_size(path.c_str());
		itoa(i_f_size, file_size);
		cout << "file_size_str=" << file_size << endl;
		snd_buf(acceptfd, file_size, FILE_SIZE);		//send file size
		cout << "sending " << file_name << endl;
		if (snd_f(path.c_str(), acceptfd) ==0)			// write file content to stream
			cout << "sent finish, " << _PATH_ << file_name << endl;
	}
	else{
		cout <<"illegal operation" << endl;
	}	
	return 0;
}

