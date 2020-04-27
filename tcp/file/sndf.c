/**
 * send file to tcp stream.
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
#include <libgen.h> 					//basename()
 
int main(int argc, char * argv[])
{
	if (argc != 3) {
		printf("请输入文件接收方的IP、端口号\n");
		return -1;
	}
	
	int port = atoi(argv[2]);
	
	int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (tcp_socket == -1) {
		perror("create socketfd is fail\n");
		return -1;
	}
	
	struct sockaddr_in dest_addr = {0};
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(port); 	
	dest_addr.sin_addr.s_addr = inet_addr(argv[1]);
	
	int ret = -1;
	ret = connect(tcp_socket, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
	if (ret != 0) {
		perror("connect failed\n");
		return -1;
	}
	
	printf("\nConnect succeed!\n");
	char file_path[128] = {0};
	char file_info[2048] = {0};
	char buf[1024] = {0};
	printf("Please enter file path: ");
	scanf("%s", file_path);
	char file_name[128] = {0};
	strncpy(file_name, basename(file_path), sizeof(file_name));
	int fd = open(file_path, O_RDWR);
	if (fd == -1) {
		printf("open [%s]  failed", file_path);
		return -1;
	}	
	int len = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	sprintf(file_info, "%d", len);
	strcpy(file_info + 16, file_name);
	write(tcp_socket, file_info, 144);
	int send_len = 0;
	while (1) {
		bzero(buf, sizeof(buf));
		ret = read(fd, buf, sizeof(buf));
		if (ret <= 0) {
			printf("send file[%s] succeed\n", file_name);
			break;
		}
		write(tcp_socket, buf, ret);
		send_len += ret;
		printf("uploading %.2f%%\n", (float)send_len/len * 100);
	}
	close(fd);
	close(tcp_socket);
	return 0;
}
