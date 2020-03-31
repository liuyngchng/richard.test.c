/**
  g++ -o _udt_server udt_server.cc /home/rd/so/libudt.so -lpthread
  ./_udt_server > /dev/null 2>&1 &
 **/
#include <arpa/inet.h>
#include "udt.h"
#include <iostream>
#include <string.h>
#define _PORT 9000
#define _BUF_SIZE_ 8096
using namespace std;

void config_socket_opt(UDTSOCKET sockfd);

int main()
{
    UDTSOCKET sockfd = UDT::socket(AF_INET, SOCK_STREAM, 0);
    config_socket_opt(sockfd);
    sockaddr_in my_addr;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(_PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(my_addr.sin_zero), '\0', 8);

    if (UDT::ERROR == UDT::bind(sockfd, (sockaddr*)&my_addr, sizeof(my_addr)))
    {
        cout << "bind port "<< _PORT << " error: " << UDT::getlasterror().getErrorMessage() << endl;
        return 0;
    }

    UDT::listen(sockfd, 10);
    cout << "listening port " << _PORT << endl;
    int namelen;
    sockaddr_in their_addr;
    while(1)
    {
        namelen=0;
        UDTSOCKET rcv_sockfd = UDT::accept(sockfd, (sockaddr*)&their_addr, &namelen);
        char ip[16];
        cout << "con from: " << inet_ntoa(their_addr.sin_addr) << ":" << ntohs(their_addr.sin_port) << endl;
        char buf[_BUF_SIZE_];
        while(1)
        {
            memset(buf,0,sizeof(buf));
            if (UDT::ERROR == UDT::recv(rcv_sockfd, buf, sizeof(buf), 0))
            {
                cout << "recv err:" << UDT::getlasterror().getErrorMessage() << endl;
                return 1;
            }
            if(strlen(buf)==0)
            {
                cout << "rec finished." << endl;
                break;
            }
            else
            {
                cout << "len: " << strlen(buf) << endl;
            }
        }
        UDT::close(rcv_sockfd);
    }
    UDT::close(sockfd);
    return 0;
}

void config_socket_opt(UDTSOCKET fd)
{
    int block[5];
    int size = sizeof(int);
    UDT::getsockopt(fd, 0, UDT_SNDBUF, &block[0], &size);
    UDT::getsockopt(fd, 0, UDT_RCVBUF, &block[1], &size);
    UDT::getsockopt(fd, 0, UDT_FC, &block[2], &size);
    UDT::getsockopt(fd, 0, UDT_MSS, &block[3], &size);
    UDT::getsockopt(fd, 0, UDT_SNDTIMEO, &block[4], &size);
    cout << "socket option" << endl;
    cout << "UDT_SNDBUF = " << block[0] << endl << "UDT_RCVBUF = " << block[1] << endl;
    cout << "UDT_FC = " << block[2] << endl << "UDT_MSS = "<< block[3] << endl;
    cout << "UDT_SNDTIMEO = " << block[4] << endl;
    cout << "start config socket option." << endl;
    int bdp = 100000;   //1000Mbps*1ms=1000Mb*10^-3=1Mb=10^6b=0.1^10^6B=100000B
    int a = 25000;
   // UDT::setsockopt(fd, 0, UDT_FC, &a, sizeof(int));
    UDT::getsockopt(fd, 0, UDT_FC, &block[2], &size);
    cout << "UDT_FC = "<< block[2] << endl;
    return; 
}
