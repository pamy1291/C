#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TYPE int
#define PH "%d "

#define REVERSE_TASK 0
#define GET_LAST_TASK 0
#define IS_LOOP_FIND_MET_TASK 0
#define MERGE_LIST_TASK 0
#define IS_Y_TASK 1

//链表节点结构
typedef struct Node {
	TYPE data;//数据
	struct Node* next;//指向下一节点指针
}Node;

//创建节点
Node* create_node(TYPE data) {
	Node* node = malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;
	return node;
}
//头添加
void add_head_list(Node* head, TYPE data) {
	Node* node = create_node(data);
	node->next = head->next;
	head->next = node;
}
//尾添加
void add_tail_list(Node* head, TYPE data) {
	Node* node = create_node(data);
	while(head->next) {
		head = head->next;
	}
	head->next = node;
}
//插入
bool insert_list(Node* head, size_t index, TYPE data) {
	for(int i=0; head->next; head = head->next,i++) {
		if(i == index) {
			Node* n = create_node(data);
			n->next = head->next;
			head->next = n;
			return true;
		}
	}
	return false;

}
//按值删除
int del_value_list(Node* head, TYPE data) {
	Node* temp;
	int cnt = 0;
	while(head->next) {//有效数据
		if(head->next->data == data) {
			temp = head->next;
			head->next = temp->next;
			free(temp);
			cnt++;
		}
		else 
			head = head->next;//继续循环
		//if(NULL == head) return cnt;//删除末尾元素时的处理
	}
	return cnt;
}
//按位置删除
bool del_index_list(Node* head, int index) {
	int i = 0;
	Node* temp;

	for(i; i<=index && head->next; head=head->next,i++) {
		temp = head;//保存前一个节点
	}
	if(index < 0 || i-1 < index) return false;	
	temp->next = head->next;
    free(head);
	return true;	
}


//访问
bool access_list(Node* head, size_t index, TYPE* data) {
	if(index < 0) return false;
	for(int i=0; i<=index; i++) {
		head = head->next;
		if(NULL == head) return false;
	}
	*data = head->data;
	return true;
}

//计数
size_t count_num_list(Node* head) {
	size_t cnt = 0;
	while(head->next) {
		cnt++;
		head = head->next;
	}
	return cnt;
}
//排序
void sort_list(Node* head) {
	for(Node* n = head->next; n->next; n = n->next) {
		for(Node* n1 = n->next; n1; n1 = n1->next) {
			if(n->data > n1->data) {
				TYPE temp = n->data;
				n->data = n1->data;
				n1->data = temp;
			}
		}
	}
}

//遍历
void show_list(Node* head) {
	Node* n = head->next;
	while(n) {
		printf(PH,n->data);
		n = n->next;
	}	
}
//销毁
void destroy_list(Node* head) {
	Node* temp;
	while(head) {
		temp = head;
		head = head->next;
		free(temp);
	}
}

/*
 *链表功能函数
 */
//链表逆序
Node* reverse_list(Node* head) {
	if(NULL == head || NULL == head->next) return head;

	Node* current = head->next;//当前节点，第一个节点
	Node* pnext = current->next;//下一个节点
	Node* pre_next = NULL;//保存节点
	current->next = NULL;//断开

	while(pnext) {//两个有效节点时进入
		pre_next = pnext->next;//保存下一个节点
		pnext->next = current;//后节点指向第一个节点
		current = pnext;//更新第一个节点
		pnext = pre_next;
	}
	head->next = current;//连接
	return head;
}
//找出单链表倒数第n个节点
Node* get_last_n_node(Node* head, int n) {
	Node* pfirst = head;//指向头节点，无效数据
	Node* psecond = NULL;

	while(n--) {
		if(NULL == pfirst) return NULL;
		pfirst = pfirst->next;
	}

	psecond = head;

	while(NULL != pfirst) {
		psecond = psecond->next;
		pfirst = pfirst->next;
	}
	return psecond;
}
//判断单链表中是否有环,返回相遇节点
Node* is_loop(Node* head, int *out) {
	Node* slow = head;//慢指针
	Node* fast = head;//快指针
	Node* met = NULL;
	while(NULL != fast && NULL != fast->next) {
		fast = fast->next->next;
		slow = slow->next;
		if(fast == slow) {
			*out = 1;
			met = fast;
			while(met != head) {
				met = met->next;
				head = head->next;
			}
			return head;
		}
	}
	*out = 0;
	return NULL;;
}
//合并两个有序链表
Node* merge_list(Node* head1, Node* head2) {
	Node* h1 = head1;
	Node* h2 = head2;
	Node* backup;//备份
	Node* head;//保存小节点头指针

	if(h1->next->data <= h2->next->data) {//保存小数据头地址
		head = h1;
		h1 = h1->next->next;//指向未比较过的节点
		h2 = h2->next;
	}else {
		head = h2;
		h2 = h2->next->next;
		h1 = h1->next;
	}

	backup = head->next;
	while(NULL !=h1 && NULL != h2) {
		if(h1->data <= h2->data) {//指向小数据节点
			backup->next = h1;
			backup = backup->next;//更新
			h1 = h1->next;
		}else {
			backup->next = h2;
			backup = backup->next;
			h2 = h2->next;
		}
	}
	//将剩下节点接上
	if(NULL != h1) backup->next = h1;
	if(NULL != h2) backup->next = h2;
	return head;
}
//判断Y形链表
bool is_y_list(Node* head1, Node* head2) {
	int len1 = count_num_list(head1);
	int len2 = count_num_list(head2);
	
	int len = len1-len2;
	
	if(len > 0) //使长度相等
		for(int i=0; i<len; i++) head1 = head1->next;
	for(int i=0; i<(-len); i++) head2 = head2->next;
	
	while(NULL != head1 && NULL != head2) {
		if(head1 == head2) {
			return true;
		}
		head1 = head1->next;
		head2 = head2->next;
	}

	return false;

}
int main(int argc,const char* argv[])
{
	TYPE data;
	Node* head = create_node(0);//头节点	
	Node* head1 = create_node(0);//头节点	
	Node* head2 = create_node(0);//头节点	
	Node* loop = head;
/*
	for(int i=0; i<5; i++) {
		add_head_list(head, i+1);
		//add_tail_list(head, 10-i);
	}
*/

/*
 *判断Y型
 */
#if IS_Y_TASK 
	Node* node_y;
    Node* temp;
	for(int i=0; i<10; i++) {
		add_head_list(head1, i+1);
		if(0 == i%2) temp = head->next; 
	}	
	for(int i=0; i<8; i++) {
		add_head_list(head2, i+11);
		node_y = head2->next;
	}	
	//node_y->next = temp;
	printf("%d\n",is_y_list(head1, head2));
#endif

#if IS_LOOP_FIND_MET_TASK
	int out;
	Node* met = NULL;
	for(int i=0; i<10; i++) {
		//add_head_list(head, i+1);
		add_tail_list(head, 10-i);
		loop = loop->next;
	}
	loop->next = head->next;
	met = is_loop(head, &out);
	printf("out:%d met:%d\n",out, met->data);
#endif


#if REVERSE_TASK 
	sort_list(head);//排序
	reverse_list(head);//逆序
	show_list(head);
#endif

#if GET_LAST_TASK
	puts("");
	Node * n = get_last_n_node(head, 1);
	printf("%d",n->data);
#endif

#if MERGE_LIST_TASK
	for(int i=0; i<5; i++) {
		add_head_list(head1, 2*(5-i)+1);
	}
	show_list(head1);
	puts("");

	for(int i=1; i<6; i++) {
		add_tail_list(head2, 2*i);
	}
	show_list(head2);
	puts("");

	Node* merge_head = merge_list(head1, head2);
	show_list(merge_head);
	puts("");

#endif
	return 0;
}
