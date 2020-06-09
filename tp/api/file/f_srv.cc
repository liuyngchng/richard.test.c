/**
  a file server to upload and download file.
  g++ -o _f_srv f_srv.cc /home/rd/so/libudt.so -lpthread
  ./_f_srv > /dev/null 2>&1 &
 **/
#include <arpa/inet.h>
#include <udt.h>
#include <cc.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#define _BUF_SIZE_ 8096
#define _BACKLOG_ 10

using namespace std;

void* rcvdata(void *);
void config_socket_opt(UDTSOCKET sockfd);

int main(int argc, char* argv[])
{
	if (argc != 2) {
		cerr <<"pls input listening port" << endl;
		return 1;
	}
	int port = atoi(argv[1]);
	UDTSOCKET sockfd;
	sockfd = UDT::socket(AF_INET, SOCK_STREAM, 0);
	config_socket_opt(sockfd);
	sockaddr_in my_addr;
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(port);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	memset(&(my_addr.sin_zero), '\0', 8);

	if (UDT::ERROR == UDT::bind(sockfd, 
		(sockaddr*)&my_addr, sizeof(my_addr))) {
		cout << "bind port "<< port << " error: " 
			 << UDT::getlasterror().getErrorMessage() << endl;
		return 0;
	}

	UDT::listen(sockfd, _BACKLOG_);
	cout << "listening port " << port << endl;
	struct sockaddr_in their_addr;
	int addrlen = sizeof(their_addr);
	while (1) {
		UDTSOCKET rcv_sockfd = UDT::accept(sockfd, (sockaddr*)&their_addr, &addrlen);
		char ip[16];
		cout << "con from: " << inet_ntoa(their_addr.sin_addr) 
			 << ":" << ntohs(their_addr.sin_port) << endl;
		pthread_t rcvthread;
		pthread_create(&rcvthread, NULL, rcvdata, new UDTSOCKET(rcv_sockfd));
		pthread_detach(rcvthread);
	}
	UDT::close(sockfd);
	return 0;
}

void* rcvdata(void* sockfd)
{
	UDTSOCKET fd = *(UDTSOCKET*) sockfd;
	char buf[_BUF_SIZE_];
	int rsize;
	while (1) {
		memset(buf, 0, sizeof(buf));
		rsize = UDT::recv(fd, buf, sizeof(buf), 0);
		if (UDT::ERROR == rsize) {
			cout << "recv err:" << UDT::getlasterror().getErrorMessage() << endl;
			return NULL;
		}
		if (strlen(buf) == 0) {
			cout << "rec finished." << endl;
			break;
		} else {
			cout << "rec: " << buf << endl;
		}
	}
	UDT::close(fd);
	return NULL;
}

void config_socket_opt(UDTSOCKET fd)
{
	int block[6];
	int size = sizeof(int);
	UDT::getsockopt(fd, 0, UDT_SNDBUF, &block[0], &size);
	UDT::getsockopt(fd, 0, UDT_RCVBUF, &block[1], &size);
	UDT::getsockopt(fd, 0, UDT_FC, &block[2], &size);
	UDT::getsockopt(fd, 0, UDT_MSS, &block[3], &size);
	UDT::getsockopt(fd, 0, UDT_SNDTIMEO, &block[4], &size);
	UDT::getsockopt(fd, 0, UDT_CC, &block[5], &size);
	cout << "socket option" << endl;
	cout << "UDT_SNDBUF = " << block[0] << endl << "UDT_RCVBUF = " << block[1] << endl;
	cout << "UDT_FC = " << block[2] << endl << "UDT_MSS = "<< block[3] << endl;
	cout << "UDT_SNDTIMEO = " << block[4] << endl << "UDT_CC = " << block[5] << endl;
	cout << "start config socket option." << endl;
	int bdp = 100000;	//1000Mbps*1ms=1000Mb*10^-3=1Mb=10^6b=0.1^10^6B=100000B
	int a = 25000;
	int result = UDT::setsockopt(fd, 0, UDT_CC, new CCCFactory<CUDPBlast>, sizeof(CCCFactory<CUDPBlast>));
    cout << "set UDT_CC return " << result << endl;
	// UDT::setsockopt(fd, 0, UDT_FC, &a, sizeof(int));
	return; 
}
