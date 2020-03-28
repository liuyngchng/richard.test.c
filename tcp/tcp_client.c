/**
   gcc -o _tcp_client tcp_client.c libmytime.so
   runtime need to ldconfig let so file can be load.
  ./_tcp_client localhost 9999 > test.log &&  2>&1
  sudo iftop -i lo  
  */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include "mytime.h"
#define _BUF_SIZE_ 8096

char* get_time();

int main(int argc, char *argv[])
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
   // memset(buf,0,sizeof(buf));
    struct sockaddr_in srv_sock;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("socket error, errno is %d, errstring is %s\n", errno, strerror(errno));
    }
    bzero(&srv_sock, sizeof(srv_sock));
    srv_sock.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &srv_sock.sin_addr);
    srv_sock.sin_port = htons(port);
    srv_sock.sin_addr.s_addr = inet_addr(ip);
    int ret = connect(sockfd, (struct sockaddr*)& srv_sock, sizeof(srv_sock));
    if (ret < 0)
    {
        printf("connect to %s:%d error, errno is %d, errstring is %s\n", ip, port, errno, strerror(errno));
        return 1;
    }
    printf("connected to %s:%d\n",ip,port);
    //buf[strlen(buf)-1]='\0';
    long long count = 0L;
    while(1)
    {   
        printf("[%s] %lld send msg: %lu\n", get_time(), ++count, strlen(buf));
        //write(sockfd, buf, strlen(buf));
       send(sockfd, buf, strlen(buf), 0);
       // break;
        //sleep(1);
        if (strncasecmp(buf,"quit", 4) == 0)
        {
            printf("quit !\n");
            break;
        }
    }
    printf("close connection.");
    close(sockfd);
    printf("exit");
    return 0;
}
