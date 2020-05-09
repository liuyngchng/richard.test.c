/**
 * agent used by client to send and receive file.
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
#include <iostream>
#include <fstream>
#include "trans.h"

#define _PORT_	9000							//server port
#define _IP_	"127.0.0.1"						//server IP
#define _PATH_	"/home/rd/test/cli/"			//client download defalt path

using namespace std;

// get file name from full path.
void get_file_name(const char path[], char file_name[]);

// write file stream named file(file full path) to sockfd 
int snd_f(const char path[], UDTSOCKET sockfd); 

// read file stream from sockfd sockfd and write to file named file
int save_f(const char path[], const int size, UDTSOCKET sockfd); 

// init socket.
UDTSOCKET init();

/**
 * send file to server.
 */
int send_file(char* path)
{
	UDTSOCKET sockfd = init();	
	char cmd[CMD_SIZE] = "put", file_name[FILE_SIZE] = {0}, file_size[FILE_SIZE] = {0};
	cout <<"send file:" << path << endl; 
	snd_buf(sockfd, cmd, CMD_SIZE);				//send cmd to server
	int i_f_size = 0;
	get_file_name(path, file_name);
	snd_buf(sockfd, file_name, FILE_SIZE);		//send file name to server
	cout << "sent file_name " << file_name << endl;
	i_f_size = get_file_size(path);
	itoa(i_f_size, file_size);
	cout << "file_size_str=" << file_size << endl;
	snd_buf(sockfd, file_size, FILE_SIZE); 
	cout << "sending " << file_name << endl;
	if (snd_f(path, sockfd) == 0)
		cout <<"upload success." << endl;	
	close(sockfd);
	return 0;
}

/**
 * get file from server.
 */
int get_file(char* file_name)
{
	UDTSOCKET sockfd = init();	
	char cmd[CMD_SIZE] = "get", file_size[FILE_SIZE] = {0};
	cout <<"get file:" << file_name << endl; 
	snd_buf(sockfd, cmd, CMD_SIZE);				//send cmd to server
	int i_f_size = 0;
	snd_buf(sockfd, file_name, FILE_SIZE);		//send file name to server
	string path = _PATH_;
	path += file_name;
	const char *p = path.c_str();
	//cout << "downloading " << p << endl;
	rcv_buf(sockfd, file_size, FILE_SIZE);		//receive file size
	cout << "file_size_str=" << file_size << endl;
	i_f_size = atoi(file_size);
	if (save_f(p, i_f_size, sockfd) == 0) {
		cout << "download success." << endl;
	} 
	close(sockfd);
	return 0;
}

/**
 * init socket connection.
 */
UDTSOCKET init()
{
	struct sockaddr_in sock_addr;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(_PORT_);
	inet_pton(AF_INET, _IP_, &sock_addr.sin_addr);
	UDTSOCKET sockfd = UDT::socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		cout << "socket fail" << endl;
		return -1;
	}
	if (UDT::ERROR == UDT::connect(sockfd, (struct sockaddr*)&sock_addr, sizeof(sock_addr))) {
		cout << "connect error" << UDT::getlasterror().getErrorMessage()<< endl;
		return -1;
	}
	return sockfd;
}
