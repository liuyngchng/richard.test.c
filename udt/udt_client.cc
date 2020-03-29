/**
  g++ -o _udt_client udt_client.cc  /home/rd/so/libudt.so -lpthread
 **/
#include <iostream>
#include "udt.h"
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#define _BUF_SIZE_ 8092

using namespace std;
using namespace UDT;

int main(int argc, char* argv[])
{
	if (argc != 3)
    {
        printf("Error: pls input server IP and port separate by blank space \n");
        return 1;
    }
    char *ip = argv[1];
    int port = atoi(argv[2]);
    printf("client will connect to server %s:%d\n", ip, port);
    char buf_init[]="hello,this is a test";
    char buf[_BUF_SIZE_];
    for(int i=0;i<sizeof(buf);i++)
    {
        buf[i]=buf_init[i%strlen(buf_init)];
    }
    UDTSOCKET sockfd = UDT::socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in srv_addr;
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &srv_addr.sin_addr);
    memset(&(srv_addr.sin_zero), '\0', 8);

    // connect to the server, implict bind
    if (UDT::ERROR == UDT::connect(sockfd, (sockaddr*)&srv_addr, sizeof(srv_addr)))
    {
        cout << "connect error: " << UDT::getlasterror().getErrorMessage();
        return 1;
    }
	cout << "connected to " << ip << ":" << port << endl;
    int count = 10000000;
    while(count>0)
	{
        count--;
    	if (UDT::ERROR == UDT::send(sockfd, buf, strlen(buf), 0))
    	{
        	cout << "send error: " << UDT::getlasterror().getErrorMessage();
        	return 2;
    	}
        cout << "send " << count << ": " << strlen(buf) << endl;
	}
    UDT::close(sockfd);
    return 0;
}
