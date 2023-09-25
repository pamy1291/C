#include "queue.h"

//	创建顺序队列
ArrayQueue* create_array_queue(size_t cal)
{
	//	申请队列结构内存
	ArrayQueue* queue = malloc(sizeof(ArrayQueue));
	//	申请存储队列元素的内存
	queue->ptr = malloc(sizeof(void*)*cal);
	//	初始化容量
	queue->cal = cal;

	queue->front = 0;
	queue->rear = -1;
	queue->cnt = 0;
	return queue;
}

//	销毁
void destroy_array_queue(ArrayQueue* queue)
{
	free(queue->ptr);
	free(queue);
}
//	队空
bool empty_array_queue(ArrayQueue* queue)
{
	return 0 == queue->cnt;
}

//	队满
bool full_array_queue(ArrayQueue* queue)
{
	return queue->cal == queue->cnt;	
}

//	入队
bool push_array_queue(ArrayQueue* queue,void* data)
{
	if(full_array_queue(queue)) return false;

	queue->rear = (queue->rear+1)%queue->cal;
	queue->ptr[queue->rear] = data;
	queue->cnt++;
	return true;
}

//	出队
bool pop_array_queue(ArrayQueue* queue)
{
	if(empty_array_queue(queue)) return false;
	queue->front = (queue->front+1)%queue->cal;
	queue->cnt--;
	return true;
}

//	队头
void* head_array_queue(ArrayQueue* queue)
{
	return queue->ptr[queue->front];	
}

//	队尾
void* tail_array_queue(ArrayQueue* queue)
{
	return queue->ptr[queue->rear];	
}

//	数量
size_t size_array_queue(ArrayQueue* queue)
{
	return queue->cnt;
}

