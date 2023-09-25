#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define TYPE int
#define PH "%d "

/*
 *双循环链表
 */
typedef struct Node{
	struct Node* prev;
	TYPE data;
	struct Node* next;
}Node;

//链表结构
typedef struct DoubleList {
	Node* head;//头指针
	size_t cnt;
}DoubleList;

//创建节点
Node* create_node(TYPE data);
//创建链表
DoubleList* create_list();
/*
 *两节点间插入新节点，依赖函数：其他函数使用
 */
 /*
void _add_node(Node* p, Node* n, TYPE data);
//删除依赖
void _del_node(Node* n);
//访问指定位置节点
Node* _access_node_index(DoubleList* l, size_t index);
//按值寻找节点依赖 do while
Node* _access_node_val(DoubleList* l, TYPE data);
*/
//头添加
void add_head_list(DoubleList* l, TYPE data);
//尾添加
void add_tail_list(DoubleList* l, TYPE data);
//位置插入
bool insert_list_index(DoubleList* l, size_t index, TYPE data);
//位置删除
bool del_list_index(DoubleList* l, size_t index);
//值删除
bool del_list_val(DoubleList* l, TYPE data);
//按位置修改
bool mod_list_index(DoubleList* l, size_t index, TYPE data);
//按值修改
bool mod_list_val(DoubleList* l, TYPE old, TYPE data);
//访问
bool access_list(DoubleList* l,size_t index, TYPE* data);
//查询，返回下标
int query_list(DoubleList* l, TYPE data);
//遍历
void show_list(DoubleList* l);

//清空
void clear_list(DoubleList* l);
//销毁
void destroy_list(DoubleList* l);

#endif//DOUBLE_LIST_H
