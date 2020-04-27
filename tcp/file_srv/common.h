/**
 * some common structure and function used in client and server.
 **/
#include<iostream>
#pragma pack(1) 		 	//单字节对齐
#define BUF_SIZE 1024 		//每次读取文件内容的大小 
#define NAME_SIZE 128 		//文件名大小 
#define CMD_SIZE 20 		//输入的操作的数组的大小 
#define FILE_SIZE 128 		//文件完整路径名的大小 

using namespace std;

/**
 * a file sturcture used to send and recieve file
 **/
struct f_file
{
	int size;  				//本次传输大小
	char buf[BUF_SIZE];  	//文件内容 
}; 

/**
 * 把buf里tLen长度数据发送至i_sockfd，直到发送完毕为止
 **/
int sndf(int i_sockfd, char* buf, size_t tLen)
{ 
	int iThisSend; 			//一次发送了多少数据 
	unsigned int iSended = 0;	//已经发送了多少 
	if (tLen == 0)
		return 0;
	while (iSended < tLen) {
		do {
			iThisSend = send(i_sockfd, buf, tLen-iSended, 0);
		} while ((iThisSend < 0) && (errno == EINTR));		//发送的时候遇到了中断 
		if (iThisSend < 0)
			return iSended;
		iSended += iThisSend;
		buf += iThisSend;
	}
	return tLen;
} 

int rcvf(int i_sockfd, char* buf, size_t tLen)
{
	int iThisRead;
	unsigned int iReaded = 0;
	if (tLen == 0)
		return 0;
	while (iReaded < tLen) {
		do {
			iThisRead = read(i_sockfd, buf, tLen-iReaded);
		} while((iThisRead < 0) && (errno == EINTR));
		if (iThisRead < 0)
			return iThisRead;
		else if (iThisRead == 0)
			return iReaded;
		iReaded += iThisRead;
		buf += iThisRead;
	}
}

/**
 * 将输入的要上传的文件路径分割出文件件名放在c数组中，
 * 例如 /home/rd/test/aaa.txt  c=aaa.txt 
**/
void get_file_name(char a[], char c[]) 
{
	int i = 0;
	for ( ; i<strlen(a) - 1 ; i++) {
		if ((a[i] == '/' && a[i+1] != '/') || (a[i] == '\\' && a[i+1] != '\\'))
			break;
		else 
			c[i] = a[i];
		//cout<<i<<endl;
	}
	if (i == strlen(a) - 1) {
  		//如果文件名里没有\ 或者/
		c[i] = a[i];
		return;
	}	
	int t = ++i;
	for ( ; i < strlen(a); i++) {
		c[i - t] = a[i];
		c[i + 1] = '\0';
	}
	c[i]='\0';
	//cout<<"c:"<<c<<endl;
}

