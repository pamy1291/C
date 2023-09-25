#include "network.h"
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <wait.h>
#include "threadpool.h"
#include "double_list.h"
#include "tools.h"

#define MSG_LEN (4096) //通信数据长度
#define CLI_MAX (50)

NetWork* snw;//服务器通信数据
ThreadPool* thread;//线程池
DoubleList* list;//链表 存储正在运行的客户端sockfd

//向其他成员发送信息
int send_to_other(NetWork* cnw, DoubleList* list, char* s) {
	for(int i=0; i<list->cnt; i++) {
		int sockfd = -1;
		access_list(list, i, &sockfd);//获取其他客户端sockfd
		if(-1 != sockfd && cnw->sockfd != sockfd) {
			if(0 >= send(sockfd, s, strlen(s)+1, 0)) {
				perror("send");
				return EXIT_FAILURE;
			}
		}
	}
	return EXIT_SUCCESS;	
}
//客户端业务逻辑函数
void con_work(void* data) {
	NetWork* cnw = (NetWork*)data;
	add_head_list(list, cnw->sockfd);//将连接的客户端存入链表
	
	char buf[MSG_LEN] = {};//通信数据	
	char name[40] = {};//消费者姓名
	//接收客户端姓名
	if(0 >= recv_nw(cnw, name, sizeof(name))) {
		printf("%s退出聊天室！\n",name);
		close(cnw->sockfd);
		del_list_val(list, cnw->sockfd);//从链表中删除
		free(cnw);
		return;
	}
	printf("%s进入聊天室\n",name);
	char cli_msg[MSG_LEN] = {};
	sprintf(cli_msg, "%s进入聊天室\n", name);
	send_to_other(cnw, list, cli_msg);
	while(1) {
		//接收消息
		if(0 >= recv_nw(cnw, buf, sizeof(buf)) || 0 == strncmp(buf, "quit", 4)) {
			printf("%s退出聊天室！\n",name);
			
			//memset(cli_msg, 0, sizeof(cli_msg));
			sprintf(cli_msg, "%s退出聊天室\n", name);
			cli_msg[strlen(cli_msg)] = '\0';//清除上次残留内容
			send_to_other(cnw, list, cli_msg);
			
			del_list_val(list, cnw->sockfd);//从链表中删除
			close(cnw->sockfd);
			free(cnw);
			return;
		}	
		printf("%s：%s\n",name, buf);//打印接收的信息	
		
		//服务端回传
		//memset(cli_msg, 0, sizeof(cli_msg));//清除上次内容
		sprintf(cli_msg, "%s：%s\n", name, buf);	
		cli_msg[strlen(cli_msg)] = '\0';
		if(EXIT_FAILURE == send_to_other(cnw, list, cli_msg)) {
			printf("%s退出聊天室！\n",name);
			
			//memset(cli_msg, 0, sizeof(cli_msg));
			sprintf(cli_msg, "%s退出聊天室\n", name);
			cli_msg[strlen(cli_msg)] = '\0';
			send_to_other(cnw, list, cli_msg);
						
			del_list_val(list, cnw->sockfd);//从链表中删除
			close(cnw->sockfd);
			free(cnw);
			return;
		}
	}//while(1)
}
//服务端业务逻辑函数
void* pro_work(void) {
	//等待连接
	NetWork* cnw =NULL;
	cnw = accept_nw(snw);
	if(NULL == cnw) {
		perror("accept_nw");
		return NULL;
	}
	if(list->cnt >= CLI_MAX) {//客户端线程已全部在服务
		char buf[MSG_LEN] = "当前人数已满，请稍后再试。\n";
		send_nw(cnw, buf, sizeof(buf));
	}
	
	return cnw;
}

//回收资源
void sigint(int num) {
	//destroy_threadpool(thread);
	destroy_list(list);
	close_nw(snw);
	exit(0);
}

int main(int argc, char* argv[]) {
	signal(SIGINT,sigint);//SIGINT信号来时执行sigint函数
	if(3 != argc)
	{
		printf("User:./chatS ip port\n");
		return 0;
	}
	list = create_list();//创建链表存储正在运行的客户端sockfd
	snw = init_nw(SOCK_STREAM,atoi(argv[2]),argv[1],true);
	if(NULL == snw)
	{
		perror("init_nw");
		free(snw);
		return -1;
	}
	//创建线程池
	thread = create_threadpool(CLI_MAX, 1, 10, con_work, pro_work);
	//启动线程池
	start_threadpool(thread);
	
	while(1);
}


