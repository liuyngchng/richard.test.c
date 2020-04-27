/**
 * receive file from tcp stream. 
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
 
int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("./recv port\n");
		return -1;
	}
	
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror("create socketfd failed\n");
		return -1;
	}
	
	struct sockaddr_in local_addr = {0};
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(atoi(argv[1])); 
	local_addr.sin_addr.s_addr = INADDR_ANY;
	int ret = bind(sockfd, (struct sockaddr *)&local_addr, sizeof(local_addr));
	if (ret == -1) {
		perror("bind  failed\n");
		return -1;
	}
	
	ret = listen(sockfd, 5);
	if (ret == -1) {
		perror("listen is fail\n");
		return -1;
	}
	
	struct sockaddr_in client_addr = {0};
	int len = sizeof(client_addr);
	printf("server is running\n");
	
	int c_sockfd = 0;
	
	while (1) {
		c_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &len);
		if (c_sockfd < 0) {
			perror("accept error\n");
			continue;
		}
		
		printf("client connected [%s:%d]\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
				
		char file_len[16] = {0};
		char file_name[128] = {0};
		char buf[1024] = {0};
		read(c_sockfd, buf, sizeof(buf));
		
		strncpy(file_len, buf, sizeof(file_len));
		strncpy(file_name, buf+sizeof(file_len), sizeof(file_name));
		printf("rcv file name:[%s] size:[%s] \n", file_name, file_len);
		sprintf(buf, "rcv-%s", file_name);
		int fd = open(buf, O_RDWR | O_CREAT | O_TRUNC, 0666);
		int size = atoi(file_len);
		int write_len = 0;
		
		while (1) {
			bzero(buf, 1024);
			ret = read(c_sockfd, buf, sizeof(buf));
			if ( ret <= 0) {
				printf("\n [recv-%s] rcv file done\n", file_name);
				break;
			}
			write(fd, buf, ret);
			write_len += ret;
			printf("rcv %.2f%% \n", (float)write_len/size * 100);
		}
		break;
	}
	
	close(c_sockfd);
	close(sockfd);
	return 0;
}
