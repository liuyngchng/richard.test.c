/*********************************************************
   
   g++ -o _tcp_server tcp_server.cc /home/rd/so/libmytime.so
   ./_tcp_server > /dev/null 2>&1 &   
   * runtime need to ldconfig let so file can be load.
  > File Name:	tcp_server.c
  > Author:		richard
  > Mail:		liuyngchng@hotmail.com
  > Created Time: Tue 02 Mar 2020 05:15:29 PM CST
 *********************************************************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "time.h"
#include <iostream>
#include <signal.h>
#define _BACKLOG_ 10
#define _BUF_SIZE_ 8096

using namespace std;

const char *inet_ntop(int af, const void *src,char *dst, socklen_t size);
char* get_time();
void catch_child(int signo);
int ret;
int main(int argc, char* argv[])
{
	if (argc != 2) {
		cerr <<"pls input listening port" << endl;
		return 1;
	}
	bool debug = false;
	int port = atoi(argv[1]);
	int sockfd = socket(AF_INET, SOCK_STREAM,0);
	if (sockfd < 0) {
		cout << get_time() <<"socket error, errno is " << errno 
			 <<", errstring is " <<  strerror(errno) << endl;
	}
	struct sockaddr_in server_sock;
	bzero(&server_sock, sizeof(server_sock));
	server_sock.sin_family = AF_INET;
	server_sock.sin_addr.s_addr = htonl(INADDR_ANY);
	server_sock.sin_port = htons(port);
	if (bind(sockfd, (struct sockaddr*)&server_sock, 
		sizeof(struct sockaddr_in))< 0) {
		cout <<"bind error, errno is " << errno 
			 << ", errstring is " << strerror(errno) << endl;
		close(sockfd);
		return 1;
	}
	if (listen(sockfd, _BACKLOG_)< 0) {
		cout << "listen error, errno is " << errno
			 << ", errstring is " <<strerror(errno) << endl;
		close(sockfd);
		return 2;
	}
	cout << "bind and listen port:" << port 
		 << " success, waiting accept..." << endl;
	struct sockaddr_in client_sock;
	socklen_t len;
	int cfd;
	while (1) {
		len = 0;
	 a: cfd = accept(sockfd, (struct sockaddr*)&client_sock,&len);
		if (cfd < 0) {
			if((errno == ECONNABORTED) || errno == EINTR) {
				goto a;
			} else {
				cout << "accept  error, errno is " << errno
					 << ", errstring is " << strerror(errno) << endl;
				return -1;
			}
		}
		pid_t pid = fork();
		if (pid < 0) {
			cout << "fork error" << endl;
			return -2;

		} else if (pid==0) {
			// child process
			close(sockfd);
			break;
		} else {
			struct sigaction act;
			act.sa_handler = catch_child;
			sigemptyset(&act.sa_mask);
			act.sa_flags = 0;
			ret = sigaction(SIGCHLD, &act, NULL);
			if (ret != 0) {
				cout << "sigaction error" << endl;
			}
			close(cfd);
			continue;
		}
	}
	char buf_ip[INET_ADDRSTRLEN];
	memset(buf_ip, 0, sizeof(buf_ip));
	inet_ntop(AF_INET, &client_sock.sin_addr, buf_ip, sizeof(buf_ip));
	cout << "get connection :ip is " << buf_ip
		 << " port is " << ntohs(client_sock.sin_port) << endl;
	char buf[_BUF_SIZE_];
	while (1) {
		memset(buf, 0, sizeof(buf));
		//read(cfd, buf, sizeof(buf));
		recv(cfd, buf, sizeof(buf), 0);
		if (strlen(buf)==0) {
			cout << "rec finished" << endl;
			break;
		}
		if (debug) {
			cout << "rcv from " << buf_ip << " : " << strlen(buf) << endl;
		}
	}
	//fflush(stdout);
	return 0;
}

void catch_child(int signo) 
{
	cout << "child task finished" << endl;	  
}
