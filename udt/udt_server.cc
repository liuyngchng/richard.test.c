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

int main()
{
    UDTSOCKET sockfd = UDT::socket(AF_INET, SOCK_STREAM, 0);
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
