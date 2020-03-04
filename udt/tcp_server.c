/*************************************************************************
 gcc tcp_server.c libtime.so -o tcp_server   
  > File Name: tcp_server.c
  > Author: richard
  > Mail: liuyngchng@hotmail.com
  > Created Time: Tue 02 Mar 2020 05:15:29 PM CST
 ************************************************************************/

#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include "time.h"
#define _PORT_ 9999
#define _BACKLOG_ 10
const char *inet_ntop(int af, const void *src,char *dst, socklen_t size);
int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM,0);
    if (sockfd < 0)
    {
        printf("socket error, errno is %d, errstring is %s\n", errno, strerror(errno));
    }
    struct sockaddr_in server_sock;
    struct sockaddr_in client_sock;
    bzero(&server_sock, sizeof(server_sock));
    server_sock.sin_family = AF_INET;
    server_sock.sin_addr.s_addr = htonl(INADDR_ANY);
    server_sock.sin_port = htons(_PORT_);
    if (bind(sockfd, (struct sockaddr*)&server_sock, sizeof(struct sockaddr_in))< 0)
    {
        printf("bind error, errno is %d, errstring is %s\n", errno, strerror(errno));
        close(sockfd);
        return 1;
    }
    if (listen(sockfd, _BACKLOG_)< 0)
    {
        printf("listen error, errno is %d, errstring is %s\n", errno, strerror(errno));
        close(sockfd);
        return 2;
    }
    printf("[%s] bind and listen port:%d success, waiting accept...\n", get_time(), _PORT_);
    while (1)
    {
        socklen_t len = 0;
        int client_socket = accept(sockfd, (struct sockaddr*)&client_sock,&len);
        if (client_socket < 0)
        {
            printf("accept  error, errno is %d, errstring is %s\n", errno, strerror(errno));
            close(sockfd);
            return 3;
        }
        char buf_ip[INET_ADDRSTRLEN];
        memset(buf_ip, 0, sizeof(buf_ip));
        inet_ntop(AF_INET, &client_sock.sin_addr, buf_ip, sizeof(buf_ip));
        printf("get connection :ip is  %s, port is %d\n ",buf_ip, ntohs(client_sock.sin_port) );
        while (1)
        {
            char buf[1024];
            memset(buf, 0, sizeof(buf));
            read(client_socket, buf, sizeof(buf));
            printf("rcv from  %s # : %s\n", buf_ip, buf);
        }
    }
    close(sockfd);
    return 0;
}
