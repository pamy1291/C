#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <wait.h>

typedef struct sockaddr* sp;

int main(int argc,const char* argv[])
{
	//socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(0 > sockfd) {
		perror("socket");
		return EXIT_FAILURE;
	}
	//准备通信地址
	struct sockaddr_in addr = {};
   	addr.sin_family = AF_INET;
	addr.sin_port = htons(6677);//2字节的端口号
	//addr.sin_addr.s_addr = inet_addr("47.97.229.46");
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int addrlen = sizeof(addr);

	if(0 > connect(sockfd, (sp)&addr, addrlen)) {
		perror("connect");
		return EXIT_FAILURE;
	}
	//父进程发送，子进程接收
	pid_t pid = fork();
	char buf[256] = {};
	printf(">>>");
	while(1) {
		//连接成功
		if(pid) {
			scanf("%s",buf);
			if(0 == strncmp(buf, "quit", 4)) {
				printf("通信结束！\n");
				close(sockfd);
				kill(pid,SIGINT);
				while(-1 != wait(NULL));
				return 0;
			}
			int ret = send(sockfd, buf, strlen(buf)+1, 0);
			if(0 >= ret) {
				printf("服务器繁忙...!\n");
				break;
			}
		}
		else {
			if(0 >= recv(sockfd, buf, sizeof(buf), 0) || 0 == strncmp(buf, "quit", 4)) {
				perror("recv");
			}
			printf("recv:%s\n>>>",buf);
			fflush(stdout);
		}
	}
	return 0;
}
