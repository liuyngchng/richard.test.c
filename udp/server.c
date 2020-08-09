#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "lt_function.h"
#define SESSION_NUM 1

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
	int insert_index = 0;
	printf("recving...\n");
	while(1) {
		char buf[10];
		recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&cli, &len);
		//receiveAndDecode(MAX_ROWNUM, buf, &SESSION_NUM, &insert_index,char*** matrix_message_decode,int*** matrix_    H_decode,int* success_recover_que,int* que_insert_pos);
		printf("%s", buf);
		char resp[] = "OK";
		sendto(sockfd, resp, sizeof(resp), 0, (struct sockaddr*)&cli, len);
	}
	close(sockfd);
}
