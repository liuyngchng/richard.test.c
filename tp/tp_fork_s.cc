/**
  g++ -o _udt_server udt_server.cc /home/rd/so/libudt.so -lpthread
  ./_udt_server > /dev/null 2>&1 &
  UDT does not support multi-process models
  (e.g., using fork system call) due to efficiency considerations,
  so this method does not work if the existing
  application uses the same sockets in multiple processes.
 **/
#include <arpa/inet.h>
#include "udt.h"
#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#define _BUF_SIZE_ 8096
#define _MODE_ 2            // 1:stream, 2:message

using namespace std;

void config_socket_opt(UDTSOCKET sockfd);
void catch_child(int signo);
int ret;

int main(int argc, char* argv[])
{
	if (argc != 2) {
        cerr <<"pls input listening port" << endl;
        return 1;
    }
    int port = atoi(argv[1]);
    UDTSOCKET sockfd;
    if (_MODE_ == 1) {
        sockfd = UDT::socket(AF_INET, SOCK_STREAM, 0);
        cout << "streaming mode" << endl;
    } else {
        sockfd = UDT::socket(AF_INET, SOCK_DGRAM, 0);
        cout << "message mode" << endl;
    }
    config_socket_opt(sockfd);
    sockaddr_in my_addr;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(my_addr.sin_zero), '\0', 8);

    if (UDT::ERROR == UDT::bind(sockfd, (sockaddr*)&my_addr, sizeof(my_addr))) {
        cout << "bind port "<< port << " error: " 
             << UDT::getlasterror().getErrorMessage() << endl;
        return 0;
    }

    UDT::listen(sockfd, 10);
    cout << "listening port " << port << endl;
    int namelen;
    sockaddr_in their_addr;
    UDTSOCKET rcv_sockfd;
	while (1) {
        namelen = 0;
     a: rcv_sockfd = UDT::accept(sockfd, (sockaddr*)&their_addr, &namelen);
		if (rcv_sockfd == UDT::INVALID_SOCK) {
            if((errno == ECONNABORTED) || errno == EINTR) {
                goto a;
            } else {
                cout << "accept  error, errno is " << errno
                     << ", errstring is " 
                     << UDT::getlasterror().getErrorMessage() << endl;
                return -1; 
            }
        }

   		pid_t pid = fork();
        if (pid < 0) {
            cout << "fork error" << endl;
            return -2; 

        } else if (pid == 0) {
            // child process
            cout << "i am child, pid " << getpid() << endl;
           // UDT::close(sockfd);
            break;
        } else {
            cout << "i am parent, pid " << getpid() << endl;
            struct sigaction act;
            act.sa_handler = catch_child;
            sigemptyset(&act.sa_mask);
            act.sa_flags = 0;
            ret = sigaction(SIGCHLD, &act, NULL);
            if (ret != 0) {
                cout << "sigaction error" << endl;
            }
            UDT::close(rcv_sockfd);
            continue;
        }
	}
    char ip[16];
    cout << "con from: " << inet_ntoa(their_addr.sin_addr) 
         << ":" << ntohs(their_addr.sin_port) << endl;
    char buf[_BUF_SIZE_];
    int rsize;
    while (1) {
        memset(buf, 0, sizeof(buf));
        if (_MODE_ == 1){
            rsize = UDT::recv(rcv_sockfd, buf, sizeof(buf), 0);
        } else {
            rsize = UDT::recvmsg(rcv_sockfd, buf, sizeof(buf));
        }
        if (UDT::ERROR == rsize) {
            cout << "recv err:" << UDT::getlasterror().getErrorMessage() << endl;
            return -2;
        }
        if (strlen(buf)==0) {
            cout << "rec finished." << endl;
            break;
        } else {
            //cout << "len: " << strlen(buf) << endl;
        }
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

void catch_child(int signo)
{
    cout << "child task finished" << endl;
}
