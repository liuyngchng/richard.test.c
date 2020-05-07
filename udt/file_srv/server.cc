/**
 * a file server, user need to input command like
 * download test.txt or upload test.txt
 */
#include <sys/types.h>
#include <udt.h>
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
#define _PORT_ 9000										//default listing port
#define _BACL_LOG_ 10
#define _PATH_ "/home/rd/test/srv/" 					//file path for server

using namespace std;

// declaration.
int save_f(const char path[], const int size, UDTSOCKET sockfd); //save stream in sockfd to file
int snd_f(const char path[], UDTSOCKET sockfd);				//send file content to stream sockfd
void get_file_name(const char path[], char name[]);

int main(int argc, char** argv){
	UDTSOCKET sockfd, acceptfd;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	
	if ((sockfd = UDT::socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		cout << "socket error";
		return -1;
	}
	cout << "socket ok" << endl;
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(_PORT_);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(my_addr.sin_zero), 0);
	if ((UDT::bind(sockfd, (struct sockaddr*)&my_addr, 
			sizeof(struct sockaddr))) == UDT::ERROR) {
		cout <<"bind error:" << UDT::getlasterror().getErrorMessage() << endl;
		return -2;
	}
	cout << "bind ok" << endl;

	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, 
		(char*)&my_addr, sizeof(my_addr)); 

	if (UDT::listen(sockfd, _BACL_LOG_) == -1) {
		perror("listen error");
		return -3;
	}
	cout << "listen ok" << endl;
	int sin_size = sizeof(my_addr);
	acceptfd = UDT::accept(sockfd, (struct sockaddr*)&my_addr, &sin_size);
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
		if (snd_f(path.c_str(), acceptfd) ==0) 			// write file content to stream
			cout << "sent finish, " << _PATH_ << file_name << endl;
	}
	else{
		cout <<"illegal operation" << endl;
	}	
	return 0;
}

