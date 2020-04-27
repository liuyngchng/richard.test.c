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

using namespace std;
#define DEFAULT_PORT 8080							//服务器端口
#define IPADDRESS "127.0.0.1"						//IP地址
#define CLI_PATH "/home/rd/test/cli/"					//客户端默认存放文件的路径名

// get file name from full path.
void get_file_name(char full_path[], char file_name[]);

// write file stream named file(file full path) to sockfd 
int upload(char file[], int sockfd); 

// read file stream from sockfd sockfd and write to file named file
int download(char file[], int sockfd); 

int main(int argc, char** argv){
	int cLen = 0;
	struct sockaddr_in sock_addr;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(DEFAULT_PORT);
	inet_pton(AF_INET, IPADDRESS, &sock_addr.sin_addr);
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		printf("socket fail!\n");
		return -1;
	}
	if (connect(sockfd, (struct sockaddr*)&sock_addr, sizeof(sock_addr)) < 0) {
		printf("connect error!\n");
		return -1;
	}
	
	char cmd[CMD_SIZE], file[FILE_SIZE];
	printf("input your opeartion:");
	scanf("%s %s", cmd, file);
  
	sndf(sockfd, cmd, CMD_SIZE); 					//send cmd to server
	if (strcmp(cmd, "upload") == 0) {
		sndf(sockfd, file, FILE_SIZE);				//send file name to server
		if (upload(file, sockfd) == 0)
			printf("upload successfully!\n");	
	} else if (strcmp(cmd, "download") == 0) {		//download a file from server	
		sndf(sockfd, file,FILE_SIZE);				//send file name to server
		if (download(file, sockfd) == 0) {
			printf("download successfully\n");
		} 
	} else {
		printf("illegal operation!\n");
	}

	close(sockfd);
	return 0;
}


int upload(char file[], int sockfd){
	f_file myfile;
	FILE* fp;
	FILE* ppp;

	if ((fp = fopen(file,"rb")) == NULL) {
		printf("cannot open file!\n");
		return -1;
	}
	printf("open file ok!\n");	

	int length;
	while (!feof(fp)) {
		length = fread(myfile.buf, sizeof(char), BUF_SIZE, fp);
		myfile.size = length;
		char *buff=new char[1500];
		int iLen=0;

		*(int*)(buff + iLen) = (int)htonl(myfile.size); //host to net long 
		iLen += sizeof(int);
		
		memcpy(buff + iLen, myfile.buf, myfile.size);
		iLen += sizeof(myfile.buf);

		ssize_t writeLen = sndf(sockfd, buff, iLen);
		if (writeLen < 0) {
			printf("write failed\n");
			close(sockfd);
			return -1;
		}
		delete[] buff;
	}
	
	fclose(fp);
	return 0;
}

/**
 * download file from server.
 * file, filename
 */
int download(char file[], int sockfd)
{ 
	char *recvMsg = new char[1500];
	int readLen;
	FILE* fp;
	f_file myfile;
	
	string path = CLI_PATH;
	path += file;
	const char *p= path.c_str();
	if ((fp = fopen(p,"ab")) == NULL){
		printf("cannot open file");
		return -1;
	}
	
	while ((readLen = rcvf(sockfd, recvMsg, sizeof(f_file))) > 0) {
		int iLen=0;
		memcpy(&myfile.size, recvMsg + iLen, sizeof(int));
		myfile.size = (int)ntohl(myfile.size);
		iLen += sizeof(int);
		memcpy(&myfile.buf, recvMsg + iLen, sizeof(myfile.buf));
		
		if (myfile.size > 0)
			fwrite(myfile.buf, sizeof(char), myfile.size, fp);
	}
	fclose(fp);
	return 0;
}
