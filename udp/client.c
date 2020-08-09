#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include "lt_function.h"

int main()
{
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1324);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	printf("pls input something:\n");
	while (1) {
		char buf[10];
		scanf("%c", buf);
		sendto(sockfd, &buf, sizeof(buf), 0, (struct sockaddr*)&addr, sizeof(addr));
		socklen_t len = sizeof(addr);
		char resp[10];
		recvfrom(sockfd, &resp, sizeof(resp), 0, (struct sockaddr*)&addr, &len);
		if (strcmp(resp,"OK") ==0) {
			//printf(" server received data\n");
		} else {
			printf("data lost\n");
		}
	}
	close(sockfd);
}
