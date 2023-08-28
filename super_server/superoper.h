#ifndef SUPEROPER_H
#define SUPEROPER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <getch.h>
#include <unistd.h>
#include "public.h"


#ifdef DEBUG
	#define debug(...) printf(__VA_ARGS__)//__VA_ARGS__替换为debug括号中的所有内容
#else
	#define debug(...)	
#endif


/*
 *交换数据
 *@a,@b：待交换的数据
 */
//#define SWAP_(a,b) {typeof(a)* t; memcpy((t),(&a),sizeof(typeof(a))); \
	memcpy((&a),(&b),sizeof(typeof(a))); memcpy((&b),(&t),sizeof(typeof(a)));}
#define SWAP_INT(a,b) {typeof(a) (t)=(a); (a)=(b); (b)=(t);}
#define SWAP_S(a,b) {typeof(a) t; strcpy(t,a); strcpy(a,b); strcpy(b,t);}

#define MAX_NAME_NUM 19//姓名最大字节数
#define MAX_MANAGER_NUM 10//最大管理员数量
#define PAGE_DIV 2

extern size_t manager_num;//当前管理员数量


//超级管理员信息
typedef struct super_message {
	char name[20];//用户名
	int pwd;//4位密码 
}SuperMessage;
extern SuperMessage* s_m;//一个超级管理员
	
//普通管理员信息
typedef struct manager_message {
	int id;//id
	char name[20];//姓名
	int pwd;//密码
	int station;//岗位，0：读者管理，1：图书管理
}ManagerMessage;
extern ManagerMessage managers[MAX_MANAGER_NUM];//MANAGER_NUM个普通管理员

//超级管理员内存创建
SuperMessage* super_create();
//加载与登录
void login_super(SuperMessage* s_m, ManagerMessage* m);	
//初始化超级管理员模块
void load_super(SuperMessage* s_m, ManagerMessage* m);
//载入普通管理员
void load_file_manager(ManagerMessage* m);
//修改超级管理密码
bool mod_pwd_super(SuperMessage* s_m);
//添加管理员
bool add_manager(ManagerMessage* m);
//删除管理员
bool del_manager(ManagerMessage* m);//根据id删除
//查找管理员,根据id查找(也可根据名字模糊查找)
void find_manager(ManagerMessage* m);//传入结构体数组
//分页显示管理员
void show_manager(ManagerMessage* m);
//批量增加管理员
bool add_many_manager(ManagerMessage* m);
//导出管理员信息为文本文件
void export_manager(ManagerMessage* m);
//保存所有数据进文件
int save(SuperMessage* s_m, ManagerMessage* m);
//排序
void manager_sort(ManagerMessage* m, int len);

#endif
