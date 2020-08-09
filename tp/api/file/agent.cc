/**
  g++ -o _agent agent.cc /home/rd/so/libudt.so -lpthread
  ./_agent 10.0.0.1 9000 -d > /dev/null 2>&1 &
 **/
#include <iostream>
#include <udt.h>
#include <cc.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#define _F_NAME_SIZE_ 8092
//#define _SND_RATE_ 400			// send rate as 800Mbps
using namespace std;
using namespace UDT;

void config_socket_opt(UDTSOCKET sockfd);
bool check_debug_mode(int argc, char* argv[]);
bool setSndRate(UDTSOCKET fd, int rate);

int main(int argc, char* argv[])
{
	if (argc < 3) {
		cerr << "pls input server IP port" << endl;
		return 1;
	}
	bool debug = check_debug_mode(argc, argv);
	char *ip = argv[1];
	int port = atoi(argv[2]);
	int sndRate = 800;
	char f_name[_F_NAME_SIZE_]= "my_test_file.docx";
	UDTSOCKET sockfd;
	sockfd = UDT::socket(AF_INET, SOCK_STREAM, 0);
	cout << "streaming mode" << endl;
	config_socket_opt(sockfd);
	sockaddr_in srv_addr;
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = htons(port);
	inet_pton(AF_INET, ip, &srv_addr.sin_addr);
	memset(&(srv_addr.sin_zero), '\0', 8);

	if (UDT::ERROR == UDT::connect(sockfd, (sockaddr*)&srv_addr, sizeof(srv_addr))) {
		cout << "connect error: " << UDT::getlasterror().getErrorMessage();
		return 1;
	}
	cout << "connected to " << ip << ":" << port << endl;
	setSndRate(sockfd, sndRate);
	int count = 0;
	int ss;
	count++;
	ss = UDT::send(sockfd, f_name, strlen(f_name), 0);
	if (UDT::ERROR == ss) {
		cout << "send error: " << UDT::getlasterror().getErrorMessage();
		return 2;
	}
	if (debug) {
	   cout << "send file name str" << ": " << f_name << endl;
	}
	UDT::close(sockfd);
	return 0;
}

bool check_debug_mode(int argc, char* argv[])
{
	bool debug =false;
	if (argc >= 4) {
		for (int i = 0; i < argc; i++) {
			if (strcmp(argv[i], "-d")==0) {
				debug = true;
				cout << "in debug mode" << endl;
			}
		}
	}
	return debug;
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
	int a = 10000;
	UDT::setsockopt(fd, 0, UDT_SNDTIMEO, &a, sizeof(int));
	int re = UDT::setsockopt(fd, 0, UDT_CC, new CCCFactory<CUDPBlast>, sizeof(CCCFactory<CUDPBlast>));
	UDT::getsockopt(fd, 0, UDT_SNDTIMEO, &block[4], &size);
	cout << "UDT_SNDTIMEO = "<< block[4] << endl << "set UDT_CC return " << re << endl;
	return;
}

bool setSndRate(UDTSOCKET fd, int rate)
{
	bool result = false;
	CUDPBlast* cchandle = NULL;
	int temp;
	UDT::getsockopt(fd, 0, UDT_CC, &cchandle, &temp);
	if (NULL == cchandle) {
		cout << "cchandle is null" << endl;
	} else {
		cchandle->setRate(rate);
		cout << "set snd rate as " << rate << "Mbps"<< endl;
		result = true;
	}
	return result;
}
