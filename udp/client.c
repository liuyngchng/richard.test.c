#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
int main()
{
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1324);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	while (1) {
		printf("pls input something：");
		char buf[10];
		scanf("%c", buf);
		sendto(sockfd, &buf, sizeof(buf), 0, (struct sockaddr*)&addr, sizeof(addr));
		socklen_t len = sizeof(addr);
		char resp[10];
		recvfrom(sockfd, &resp, sizeof(resp), 0, (struct sockaddr*)&addr, &len);
		if (resp == "OK") {
			printf(" server received data\n");
		} else {
			printf("server lost data\n");
		}
	}
	close(sockfd);
}
