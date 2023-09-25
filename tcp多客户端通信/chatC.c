#include "threadpool.h"
#include "network.h"
#include "tools.h"
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <wait.h>

#define MSG_LEN (4096)

NetWork* cnw;

int main(int argc, char* argv[]) {
	if(3 != argc)
	{
		printf("User:./chatC ip port\n");
		return 0;
	}
	
	cnw = init_nw(SOCK_STREAM,atoi(argv[2]),argv[1],false);
	if(NULL == cnw)
	{
		perror("init_nw");
		free(cnw);
		return -1;
	}
	char name[40] = {};
	printf("请输入聊天名称：");
	scanf("%s",name);
	if(0 >= send_nw(cnw, name, strlen(name)+1)) {
		printf("服务器繁忙！请稍后重试\n");
		return EXIT_FAILURE;
	}
	
	pid_t pid = fork();
	char buf[MSG_LEN] = {};
	while(1) {
		//连接成功
		if(pid) {//父进程发送信息
			printf(":");
			get_string(buf, MSG_LEN);
			int ret = send_nw(cnw, buf, strlen(buf)+1);
			if(0 >= ret) {
				printf("服务器繁忙...!\n");
				break;
			}			
			if(0 == strncmp(buf, "quit", 4)) {//结束通信
				close(cnw->sockfd);
				kill(pid,SIGINT);
				while(-1 != wait(NULL));
				return 0;
			}
		}
		else {//接收消息
			if(0 >= recv_nw(cnw, buf, sizeof(buf)) || 0 == strncmp(buf, "quit", 4)) {
				perror("recv");
			}
			printf("\r                                              %s\n:",buf);
			fflush(stdout);
		}
	}
}
