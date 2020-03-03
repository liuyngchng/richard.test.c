#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<arpa/inet.h>

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
    char buf[]="hello,this is a test";
   // memset(buf,0,sizeof(buf));
    struct sockaddr_in server_sock;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        printf("socket error, errno is %d, errstring is %s\n", errno, strerror(errno));
    }
    bzero(&server_sock, sizeof(server_sock));
    server_sock.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &server_sock.sin_addr);
    server_sock.sin_port = htons(port);
    int ret = connect(sock, (struct sockaddr*)& server_sock, sizeof(server_sock));
    if (ret < 0)
    {
        printf("connect to %s:%d error, errno is %d, errstring is %s\n", ip, port, errno, strerror(errno));
        return 1;
    }
    printf("connect to %s:%d sucess\n",ip,port);
    while(1)
    {
        buf[strlen(buf)-1] = '\0';
        write(sock, buf, sizeof(buf));
        if (strncasecmp(buf,"quit", 4) == 0)
        {
            printf("quit !\n");
            break;
        }
    }
    close(sock);
    return 0;
}
