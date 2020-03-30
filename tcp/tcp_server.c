/*********************************************************
   
   gcc -o _tcp_server tcp_server.c /home/rd/so/libmytime.so
   ./_tcp_server > /dev/null 2>&1 &   
   * runtime need to ldconfig let so file can be load.
  > File Name:  tcp_server.c
  > Author:     richard
  > Mail:       liuyngchng@hotmail.com
  > Created Time: Tue 02 Mar 2020 05:15:29 PM CST
 *********************************************************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "time.h"
#define _PORT_ 9999
#define _BACKLOG_ 10
#define _BUF_SIZE_ 8096
const char *inet_ntop(int af, const void *src,char *dst, socklen_t size);
char* get_time();
int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM,0);
    if (sockfd < 0)
    {
        printf("[%s] socket error, errno is %d, errstring is %s\n", get_time(), errno, strerror(errno));
    }
    struct sockaddr_in server_sock;
    bzero(&server_sock, sizeof(server_sock));
    server_sock.sin_family = AF_INET;
    server_sock.sin_addr.s_addr = htonl(INADDR_ANY);
    server_sock.sin_port = htons(_PORT_);
    if (bind(sockfd, (struct sockaddr*)&server_sock, sizeof(struct sockaddr_in))< 0)
    {
        printf("[%s] bind error, errno is %d, errstring is %s\n", get_time(), errno, strerror(errno));
        close(sockfd);
        return 1;
    }
    if (listen(sockfd, _BACKLOG_)< 0)
    {
        printf("[%s] listen error, errno is %d, errstring is %s\n", get_time(), errno, strerror(errno));
        close(sockfd);
        return 2;
    }
    printf("[%s] bind and listen port:%d success, waiting accept...\n", get_time(), _PORT_);
    struct sockaddr_in client_sock;
    socklen_t len;
    while (1)
    {
        len = 0;
        int cfd = accept(sockfd, (struct sockaddr*)&client_sock,&len);
        if (cfd < 0)
        {
            printf("[%s] accept  error, errno is %d, errstring is %s\n", get_time(), errno, strerror(errno));
            close(sockfd);
            return 3;
        }
        char buf_ip[INET_ADDRSTRLEN];
        memset(buf_ip, 0, sizeof(buf_ip));
        inet_ntop(AF_INET, &client_sock.sin_addr, buf_ip, sizeof(buf_ip));
        printf("[%s] get connection :ip is  %s, port is %d\n", get_time(), buf_ip, ntohs(client_sock.sin_port) );
        char buf[_BUF_SIZE_];
        while (1)
        {
            memset(buf, 0, sizeof(buf));
            //read(cfd, buf, sizeof(buf));
            recv(cfd, buf, sizeof(buf), 0);
            if (strlen(buf)==0)
            {
                printf("[%s] rec finished.\n", get_time());
                break;
            }
            else
            {
                printf("[%s] rcv from  %s # : %lu\n", get_time(), buf_ip, strlen(buf));
            }
        }
        //fflush(stdout);
    }
    close(sockfd);
    return 0;
}
