
#include "double_list.h"

/*
 *双循环链表
 */
//创建节点
Node* create_node(TYPE data) {
	Node* node = malloc(sizeof(Node));
	node->data = data;
	node->prev = node;
	node->next = node;
	return node;
}
//创建链表
DoubleList* create_list() {
	DoubleList* list = malloc(sizeof(DoubleList));
	list->head = create_node(0);
	list->cnt = 0;
	return list;
}
/*
 *两节点间插入新节点，依赖函数：其他函数使用
 */
void _add_node(Node* p, Node* n, TYPE data) {
	Node* node = create_node(data);
	node->next = n;
	node->prev = p;
	p->next = node;
	n->prev = node;
}
//删除依赖
void _del_node(Node* n) {
	n->prev->next = n->next;
	n->next->prev = n->prev;
	free(n);
}
//访问指定位置节点
Node* _access_node_index(DoubleList* l, size_t index) {
	if(NULL == l) return NULL;
	if(index >= l->cnt) return NULL;
	Node* node;
	int i = 0;
	if(index < l->cnt/2) {
		for(i=0, node=l->head->next; i<index; i++) {
			node = node->next;
			if(node == l->head) return NULL;
		}
	}else {
		for(i=l->cnt-1, node=l->head->prev; i>index; i--) {
			node = node->prev;
			if(node == l->head->prev) return NULL;
		}
	}
	return node;
}
//按值寻找节点依赖 do while
Node* _access_node_val(DoubleList* l, TYPE data) {
	if(NULL  == l) return NULL;
	if(l->cnt == 0) return NULL;
	Node *n = l->head->next;
	do{
		if(data == n->data) return n;
		n = n->next;
	}while(n != l->head);
	return NULL; 
}
//头添加
void add_head_list(DoubleList* l, TYPE data) {
	_add_node(l->head, l->head->next, data);
	l->cnt++;
}
//尾添加
void add_tail_list(DoubleList* l, TYPE data) {
	_add_node(l->head->prev, l->head, data);	
	l->cnt++;
}
//位置插入
bool insert_list_index(DoubleList* l, size_t index, TYPE data) {
	Node* n = _access_node_index(l, index);
	if(NULL == n) return false;

	_add_node(n->prev, n, data);
	l->cnt++;
	return true;
}
//位置删除
bool del_list_index(DoubleList* l, size_t index) {
	Node* n = _access_node_index(l, index);
	if(NULL == n) return false;
	_del_node(n);
	l->cnt--;
	return true;
}
//值删除
bool del_list_val(DoubleList* l, TYPE data) {
	Node* n = _access_node_val(l, data);
	if(NULL == n) return false;

	_del_node(n);
	l->cnt--;
	return true;
}
//按位置修改
bool mod_list_index(DoubleList* l, size_t index, TYPE data) {
	Node* n = _access_node_index(l, index);
	if(NULL == n) return false;
	n->data = data;
	return true;
}
//按值修改
bool mod_list_val(DoubleList* l, TYPE old, TYPE data) {
	Node* n = _access_node_val(l, old);
	if(NULL == n) return false;
	n->data = data;
	return true;
}
//访问
bool access_list(DoubleList* l,size_t index, TYPE* data) {
	Node* n = _access_node_index(l, index);
	if(NULL == n) return false;
	*data = n->data;
	return true;
}
//查询，返回下标
int query_list(DoubleList* l, TYPE data) {
	Node* n = l->head->next;
	int cnt = 0;
	while(n!=l->head) {
		if(n->data == data) return cnt;
		n = n->next;
		cnt++;
	}
	return -1;
}
//遍历
void show_list(DoubleList* l) {
	if(0 == l->cnt) return;
	Node* n = l->head->next;
	do{
		printf(PH,(n->data));
		n = n->next;
	}while(n != l->head);
	puts("");
}

//清空
void clear_list(DoubleList* l) {
	while(l->cnt) {
		del_list_index(l,0);
	}
}
//销毁
void destroy_list(DoubleList* l) {
	clear_list(l);
	free(l->head);
	free(l);
}

