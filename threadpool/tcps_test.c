#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "threadpool.h"

typedef struct sockaddr* sp;

int sockfd;//服务连接客户端的sockfd

//消费者业务逻辑函数
void con_work(void* data) {
	int* cli_sockfd = (int*)data;
	char buf[256] = {};//通信数据	
	while(1) {
		//接收请求
		if(0 >= recv(*cli_sockfd, buf, sizeof(buf), 0) || 0 == strncmp(buf, "quit", 4)) {
			printf("客户端 %d 退出！\n",*cli_sockfd);
			close(*cli_sockfd);
			free(cli_sockfd);
			return;
		}
		printf("\nfrom %d recv:%s\n",*cli_sockfd, buf);
		//回声服务器
		strcat(buf,":server send");
		if(0 >= send(*cli_sockfd, buf, strlen(buf)+1, 0)) {
			printf("客户端 %d 退出!\n",*cli_sockfd);
			close(*cli_sockfd);
			free(cli_sockfd);
			return;
		}
	}
}
//生产者业务逻辑函数
void* pro_work(void) {
	//等待连接
	struct sockaddr_in cli_addr;//连接者ip信息
	socklen_t addrlen = sizeof(cli_addr);
	int* cli_sockfd = malloc(sizeof(int));
	*cli_sockfd = accept(sockfd, (sp)&cli_addr, &addrlen);
	if(0 > *cli_sockfd) {
		perror("accept");
		return NULL;
	}
	return cli_sockfd;
}

int main(int argc,const char* argv[])
{
	//创建socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(0 > sockfd) {
		perror("socket");
		return EXIT_FAILURE;
	}
	//准备通信地址
	struct sockaddr_in addr = {};
   	addr.sin_family = AF_INET;
	addr.sin_port = htons(6677);//2字节的端口号
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");//服务器所在ip

	//绑定
	socklen_t addrlen = sizeof(addr);
	if(0 > bind(sockfd, (sp)&addr, addrlen)) {
		perror("bind");
		return EXIT_FAILURE;
	}
	//监听
	if(0 > listen(sockfd, 5)) {
		perror("listen");
		return EXIT_FAILURE;
	}
	//创建线程池
	ThreadPool* thread = create_threadpool(5, 1, 10, con_work, pro_work);
	//启动线程池
	start_threadpool(thread);
	while(1) {
		
	}
	return 0;
}
