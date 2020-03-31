/**
  g++ -o _udt_client udt_client.cc  /home/rd/so/libudt.so -lpthread
  ./_udt_client 10.0.0.1 9000 > /dev/null 2>&1 &
  ifstat > tp.dat &
 **/
#include <iostream>
#include "udt.h"
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#define _BUF_SIZE_ 8092
#define _MODE_ 2              // 1:streaming , 2:msg 
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
    char buf_init[]="hello,this is a test";
    char buf[_BUF_SIZE_];
    for(int i=0;i<sizeof(buf);i++)
    {
        buf[i]=buf_init[i%strlen(buf_init)];
    }
    UDTSOCKET sockfd;
    if (_MODE_ == 1)
    {
        sockfd = UDT::socket(AF_INET, SOCK_STREAM, 0);
        cout << "streaming mode" << endl;
    }
    else
    {
        sockfd = UDT::socket(AF_INET, SOCK_DGRAM, 0);
        cout << "message mode" << endl;
    }
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
    int ss;
    while(count>0)
	{
        count--;
    	if (_MODE_ == 1)
        {
            ss = UDT::send(sockfd, buf, strlen(buf), 0);
        }
        else
        {
            ss = UDT::sendmsg(sockfd, buf, strlen(buf), -1, false);
        }
        if (UDT::ERROR == ss)
    	{
        	cout << "send error: " << UDT::getlasterror().getErrorMessage();
        	return 2;
    	}
        else
        {
           // cout << "send " << count << ": " << ss << endl;
        }
	}
    UDT::close(sockfd);
    return 0;
}
