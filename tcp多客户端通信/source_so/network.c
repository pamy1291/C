#include "network.h"

/*
typedef struct NetWork {
	int type;//通信协议
	int sockfd;//socket对象
	struct sockaddr_in addr;//通信地址
	socklen_t addrlen;//通信结构体长度
	bool is_svr;//是否为服务端
}NetWork;*/

//分配内存、创建socket、初始化通信地址、绑定、监听、连接(客户端)
NetWork* init_nw(int type, uint16_t port, const char* ip, bool is_svr) {
	NetWork* nw = malloc(sizeof(NetWork));
	nw->type = type;//数据流tcp/数据报udp
	if(0 > (nw->sockfd = socket(AF_INET, type, 0))) {
		perror("sockfd");
		free(nw);
		return NULL;
	}
	//初始化
	nw->addr.sin_family = AF_INET;
	nw->addr.sin_port = htons(port);
	nw->addr.sin_addr.s_addr = inet_addr(ip);
	nw->addrlen = sizeof(struct sockaddr_in);
	
	//是否为服务器
	nw->is_svr = is_svr;
	
	//服务端
	if(is_svr == true) {
		//绑定
		if(0 > bind(nw->sockfd, (struct sockaddr*)&(nw->addr), nw->addrlen)) {
			perror("bind");
			free(nw);
			return NULL;
		}	
		//数据流/tcp 监听
		if(SOCK_STREAM == type) {
			if(0 > listen(nw->sockfd, 128)) {
				perror("listen");
				free(nw);
				return NULL;
			}
		}
	}
	else if(SOCK_STREAM == type){//tcp客户端
		if(0 > connect(nw->sockfd, (struct sockaddr*)&(nw->addr), nw->addrlen)) {
			perror("connect");
			free(nw);
			return NULL;
		}
	}
	return nw;
}

//等待连接 只能TCP的服务端执行
NetWork* accept_nw(NetWork* svr_nw) {
	if(SOCK_STREAM == svr_nw->type && svr_nw->is_svr) {
		NetWork* apt_nw = malloc(sizeof(NetWork));//存accept的结果,及连接者信息
		memcpy(apt_nw, svr_nw, sizeof(NetWork));
		int apt_sockfd = accept(svr_nw->sockfd, (struct sockaddr*)&(apt_nw->addr),
						&(apt_nw->addrlen));
		if(0 > apt_sockfd) {
			perror("accept");
			free(apt_nw);
			return NULL;
		}
		apt_nw->sockfd = apt_sockfd;
		return apt_nw;
	}
	//udp
	printf("类型不匹配！\n");
	return NULL;
}

//发送数据tcp/udp len:需要发送的数据字节
int send_nw(NetWork* nw, void* buf, size_t len) {
	int ret = 0;
	//tcp
	if(SOCK_STREAM == nw->type) {
		ret = send(nw->sockfd, buf, len, 0);
	    if(0 >= ret) {
			perror("send");
			return -1;
		}
		return ret;
	}
	//udp
	ret = sendto(nw->sockfd, buf, len, 0, 
			(struct sockaddr*)&(nw->addr), nw->addrlen);
	if(0 >= ret) {
		perror("sendto");
		return -1;
	}
	return ret;
}

//接收数据
int recv_nw(NetWork* nw, void* buf, size_t len) {
	//tcp
	if(SOCK_STREAM == nw->type) {
		int ret = 0;
		ret = recv(nw->sockfd, buf, len, 0);	    
		if(0 >= ret) {
			perror("recv");
			return -1;
		}
		return ret;
	}
	//udp
	ssize_t ret = recvfrom(nw->sockfd, buf, len, 0, 
			(struct sockaddr*)&(nw->addr), &nw->addrlen);
	if(0 >= ret) {
		perror("recvfrom");
		return -1;
	}
	return ret;	
}

//关闭socket且释放内存
void close_nw(NetWork* nw) {
	close(nw->sockfd);
	free(nw);
}

