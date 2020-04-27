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
using namespace std;
#define DEFAULT_PORT 8080	//默认服务器端口
#define BACKLOG 10
#define PATH "/home/rd/test/srv/" //默认服务器存放文件的路径

int getFileFromClient(char filename[],int acceptfd); //从客户端接收文件
int sendFileToClient(char filename[],int acceptfd);	//发送文件给客户端


int main(int argc,char** argv){
	int sockfd,acceptfd;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	unsigned int sin_size;
	
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1){
		printf("socket error");
		return -1;
	}
	printf("socket ok\n");
	my_addr.sin_family=AF_INET;
	my_addr.sin_port=htons(DEFAULT_PORT);
	my_addr.sin_addr.s_addr=INADDR_ANY;
	bzero(&(my_addr.sin_zero),0);
	if((bind(sockfd,(struct sockaddr*)&my_addr,sizeof(struct sockaddr)))==-1){
		printf("bind error\n");
		return -2;
	}
	printf("bind ok!\n");

	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char*)&my_addr, sizeof(my_addr)); //设置端口在TIME_WAIT状态下可重用 

	if(listen(sockfd,BACKLOG)==-1){
		perror("listen error:");
		return -3;
	}
	printf("listen ok\n");
	sin_size=sizeof(my_addr);
	acceptfd=accept(sockfd,(struct sockaddr*)&my_addr,&sin_size);
	if(acceptfd<0){
		close(sockfd);
		printf("accept failed!\n");
		return -4;
	}
	printf("accept ok\n");
	
	char opera[CMD_SIZE];//存放客户端发送来的操作：upload || download
	char com_file[FILE_SIZE];//存放客户端发送来的文件名 
	rcvf(acceptfd,opera,CMD_SIZE);	//接收客户端发送来的操作
	
	if(strcmp(opera,"upload")==0){		//客户端是执行upload操作 
		printf("updating....\n");
		rcvf(acceptfd,com_file,FILE_SIZE);// 客户端要上传的文件名 
		if(getFileFromClient(com_file,acceptfd)==0)
			printf("Get file successfully!\n");
	}else if(strcmp(opera,"download")==0){ //客户端执行download操作
		printf("downloading....\n");
		rcvf(acceptfd,com_file,FILE_SIZE);//还要从客户端接收要哪个文件
		if(sendFileToClient(com_file,acceptfd)==0){
			printf("Send file successfully!\n");
		}
	}
	else{
		printf("illegal operation!\n");
	}	
	return 0;
}

int getFileFromClient(char filename[],int acceptfd){//接收客户端发来的文件，返回0表示成功
	char *recvMsg=new char[1500];
	int readLen;
	FILE* fp;
	f_file myfile; //f_file结构体，存放文件信息
//	ofstream of("bbb.txt",ios::out|ios::app);

	char part_file[FILE_SIZE];
	get_file_name(filename, part_file); 
	string path=PATH;
	path+=part_file;
	const char *p=path.c_str();
	if((fp=fopen(p,"a"))==NULL){ //打开方式ab,从文件后追加，那么多次写就不用定位文件指针，直接在文件后面追加就可以了
			printf("cannot open file");
			return -1;
	}

	while((readLen=recv(acceptfd,recvMsg,sizeof(f_file),0))>0){
		//Myfile结构体操作，将客户端发来的结构体信息录入
		int iLen=0;

		memcpy(&myfile.size,recvMsg+iLen,sizeof(int));
		myfile.size=(int)ntohl(myfile.size);
		iLen+=sizeof(int);

		memcpy(&myfile.buf,recvMsg+iLen,myfile.size);
		if(myfile.size>0)
			fwrite(myfile.buf,sizeof(char),BUF_SIZE,fp);
	}
	
	fclose(fp);
	return 0;
}

int sendFileToClient(char filename[],int acceptfd){  //发送文件给客户端
	f_file myfile;
	FILE* fp;

	string s=PATH;
    s+=filename;
    const char *fileP=s.c_str();  //文件在服务器端的完整路径名
	if((fp=fopen(fileP,"rb"))==NULL){
		printf("cannot open file!\n");
		return -1;
	}
	printf("openfile ok!\n");
		
	int length;
	while((length=fread(myfile.buf,sizeof(char),BUF_SIZE,fp))>0){

		myfile.size=length;
		char *pBuff=new char[1500];
  //存放myfile结构体中的数据
		int iLen=0;
		
		*(int*)(pBuff+iLen)=htonl(myfile.size);
		iLen+=sizeof(int);
		memcpy(pBuff+iLen,myfile.buf,sizeof(myfile.buf));
		iLen+=sizeof(myfile.buf);
		ssize_t writeLen=sndf(acceptfd,pBuff,iLen);	//发送pBuff给客户端

		if(writeLen<0){
			printf("write failed\n");
			close(acceptfd);
			return -1;
		}
		delete[] pBuff;
	}
	
	fclose(fp);
	return 0;
}
