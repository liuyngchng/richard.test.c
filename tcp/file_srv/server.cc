/**
 * a file server, user need to input command like
 * download test.txt or upload test.txt
 */
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
#include<fstream>
#include<iostream>
#include"common.h"
#define _PORT_ 8080									//default listing port
#define _BACL_LOG_ 10
#define _PATH_ "/home/rd/test/srv/" 				//file path for server

using namespace std;

// declaration.
int save_f(char file_name[], int acceptfd); 		//save stream in acceptfd to file
int snd_f(char file_name[],int acceptfd);			//send file content to stream acceptfd


int main(int argc, char** argv){
	int sockfd, acceptfd;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		cout << "socket error";
		return -1;
	}
	cout << "socket ok" << endl;
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(_PORT_);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(my_addr.sin_zero), 0);
	if ((bind(sockfd, (struct sockaddr*)&my_addr, 
			sizeof(struct sockaddr))) == -1) {
		cout <<"bind error" << endl;
		return -2;
	}
	cout << "bind ok" << endl;

	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, 
		(char*)&my_addr, sizeof(my_addr)); 

	if (listen(sockfd, _BACL_LOG_) == -1) {
		perror("listen error");
		return -3;
	}
	cout << "listen ok" << endl;
	unsigned int sin_size = sizeof(my_addr);
	acceptfd = accept(sockfd, (struct sockaddr*)&my_addr, &sin_size);
	if (acceptfd < 0) {
		close(sockfd);
		cout << "accept failed" << endl;
		return -4;
	}
	cout << "accept ok" << endl;
	
	char cmd[CMD_SIZE] = {0};						//save cmd：get || put 
	char file_name[FILE_SIZE] = {0};				//file_name from client 
	rcv_buf(acceptfd, cmd, CMD_SIZE);				//receive cmd
	if (strcmp(cmd, "put") == 0) {
		cout << "cmd is " << cmd << endl;
		rcv_buf(acceptfd, file_name, FILE_SIZE);	//receive file name 
		cout << "uploading file " << file_name << endl;
		if (save_f(file_name, acceptfd) == 0)		//receive stream and save to file
			cout <<"saved " << _PATH_ << file_name << endl;
	} else if (strcmp(cmd, "get") == 0) {
		cout <<"cmd is " << cmd << endl;
		rcv_buf(acceptfd, file_name, FILE_SIZE);	//receive file name
		if (snd_f(file_name, acceptfd) ==0) 		// write file content to stream
			cout << "send file " << _PATH_ << file_name << endl;
	}
	else{
		cout <<"illegal operation" << endl;
	}	
	return 0;
}

/**
 * save file content from stream represented by acceptfd
 * to file name file_name.
**/
int save_f(char file_name[], int acceptfd)
{
	//f_file myfile; 
	//ofstream of("bbb.txt",ios::out|ios::app);

	char part_file[FILE_SIZE] = {0};
	get_file_name(file_name, part_file); 
	string path = _PATH_;
	path += part_file;
	const char *p = path.c_str();
	FILE* fp;
	if ((fp = fopen(p, "a")) == NULL) {
		cout << "cannot open file" << endl;
		return -1;
	}
	int rd_l;
	char *buf = new char[1500];
	while ((rd_l = recv(acceptfd, buf, sizeof(buf), 0)) > 0) {
		int i_len = 0;
		//memcpy(&myfile.size, buf + i_len, sizeof(int));
		//myfile.size = (int)ntohl(myfile.size);
		i_len += sizeof(int);

		//memcpy(&myfile.buf, buf + i_len, myfile.size);
		if (rd_l > 0)
			fwrite(buf, sizeof(char), rd_l, fp);
	}
	fclose(fp);
	return 0;
}

/**
 * send file stream to acceptfd
 */
int snd_f(char file_name[], int acceptfd)
{
	f_file myfile;
	FILE* fp;
	string s = _PATH_;
    s += file_name;
    const char *file_path = s.c_str();
	if((fp = fopen(file_path,"rb")) == NULL){
		cout <<"cannot open file" << endl;
		return -1;
	}
	cout << "open file " << file_path << endl;
		
	int length;
	while ((length = fread(myfile.buf, sizeof(char), BUF_SIZE, fp)) > 0) {

		myfile.size = length;
		char *buffer = new char[1500];
		int i_len = 0;
		
		*(int*)(buffer + i_len) = htonl(myfile.size);
		i_len += sizeof(int);
		memcpy(buffer+i_len, myfile.buf, sizeof(myfile.buf));
		i_len += sizeof(myfile.buf);
		ssize_t writeLen = snd_buf(acceptfd, buffer, i_len);	

		if (writeLen < 0) {
			cout << "write failed" << endl;
			close(acceptfd);
			return -1;
		}
		delete[] buffer;
	}
	
	fclose(fp);
	return 0;
}
