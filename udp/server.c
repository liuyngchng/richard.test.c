#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1324);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int ret = bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
	if (ret < 0 ) {
		printf("bind error\n");
		return -1;

	}
	struct sockaddr_in cli;
	socklen_t len=sizeof(cli);

	while(1) {
		printf("recving...\n");
		char buf[10];
		recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&cli, &len);
		printf("recv %s\n", buf);
		char resp[] = "OK";
		sendto(sockfd, resp, sizeof(resp), 0, (struct sockaddr*)&cli, len);
	}
	close(sockfd);
}
