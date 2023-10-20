#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <pthread.h>
#include "queue.h"

//	消费者线程真正的业务逻辑函数 由调用者提供
typedef void (*con_WorkFP)(void*);
//	生产者线程真正的业务逻辑函数 由调用者提供
typedef void* (*pro_WorkFP)(void);

typedef struct ThreadPool
{
	int con_thread_cnt;		//	消费者线程数量
	pthread_t* con_tids;	//	消费者线程id
	int pro_thread_cnt;		//	生产者线程数量
	pthread_t* pro_tids;	//	生产者线程id
	ArrayQueue* store;		//	队列仓库
	con_WorkFP con_work;	//	消费者业务逻辑函数
	pro_WorkFP pro_work;	//	生产者业务逻辑函数
	pthread_mutex_t hlock;	//	队头锁
	pthread_mutex_t tlock;	//	队尾锁
	pthread_cond_t empty;	//	空仓条件变量
	pthread_cond_t full;	//  满仓条件变量
}ThreadPool;

//	创建线程池并初始化
ThreadPool* create_threadpool(int con_cnt,int pro_cnt,int store_cal,con_WorkFP con_fp,pro_WorkFP pro_fp);

//	启动线程池
void start_threadpool(ThreadPool* thread);

//	生产数据
void push_threadpool(ThreadPool* thread,void* data);

//	消费数据
void* pop_threadpool(ThreadPool* thread);

//	销毁线程池
void destroy_threadpool(ThreadPool* thread);

#endif//THREADPOOL_H







