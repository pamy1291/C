#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct NetWork {
	int type;//通信协议
	int sockfd;//socket对象
	struct sockaddr_in addr;//通信地址
	socklen_t addrlen;//通信结构体长度
	bool is_svr;//是否为服务端
}NetWork;

//分配内存、创建socket、初始化通信地址、绑定、监听、连接
NetWork* init_nw(int type, uint16_t port, const char* ip, bool is_svr);

//等待连接 只能TCP的服务端执行
NetWork* accept_nw(NetWork* svr_nw);

//发送数据tcp/udp len:需要发送的数据字节
int send_nw(NetWork* nw, void* buf, size_t len);

//接收数据
int recv_nw(NetWork* nw, void* buf, size_t len);

//关闭socket且释放内存
void close_nw(NetWork* nw);

#endif//NETWORK
