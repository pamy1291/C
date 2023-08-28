#include "superoper.h"

/*
 *需要用到的全局变量
 */
size_t manager_num = 0;//当前管理员数量
ManagerMessage managers[MAX_MANAGER_NUM] = {};//普通管理员
SuperMessage* s_m = NULL;//超级管理员


/*
 *保存所有数据进文件: 超级管理员文件及普通管理员文件
 */
int save(SuperMessage* s_m, ManagerMessage* m) {
	debug("%s\n",__func__);
	FILE* f_super = fopen("files/super", "w");
	//保存超级管理员信息
	fwrite(s_m, 1, sizeof(SuperMessage), f_super);
	fclose(f_super);
	printf("超级管理员信息已保存。\n");

	//保存普通管理员信息
	FILE* f_m = fopen("files/manager", "w");
	int cnt = 0;//成功写入的普通管理员个数
	int ret_m = 0;//一次写入成功的字节
	for(int i=0; i<MAX_MANAGER_NUM; i++) {
		ret_m = fwrite(&m[i], 1, sizeof(ManagerMessage), f_m);
		cnt++;
	}
	fclose(f_m);
	printf("普通管理员信息已保存。\n即将退出！\n");
	return cnt;
}

/*
 *显示菜单
 */
void menu() {
	puts("******超级管理员系统******");
	puts("*    1.修改密码");
	puts("*    2.添加管理员");
	puts("*    3.删除管理员");
	puts("*    4.查找管理员");
	puts("*    5.显示所有管理员");
	puts("*    6.批量增加管理员");
	puts("*    7.导出管理员");
	puts("*    q.退出");
	puts("************************");
}

/*
 *修改超级管理密码
 */
bool mod_pwd_super(SuperMessage* s_m) {
	debug("%s\n",__func__);
	int old_pwd,new_pwd,pre_new;
	int cnt = 2;
	
in_old:	//旧密码输入
	printf("您还剩%d次机会！\n",cnt--);
	printf("请输入旧密码：\n");
	//scanf("%d", &old_pwd);
	old_pwd = no_show_num();//无回显方式获取密码
	stdin->_IO_read_ptr = stdin->_IO_read_end;//清残留换行
	if(old_pwd == s_m->pwd) {
in_new:	//新密码输入
		printf("请输入新密码：\n");
		//scanf("%d", &new_pwd);
		new_pwd = no_show_num();
		stdin->_IO_read_ptr = stdin->_IO_read_end;//清残留换行
		//判断位数
		if(num_order(new_pwd) != 4) {
			printf("请输入4位有效数字作为密码！\n");
			goto in_new;
		}
		printf("请确认新密码：\n");
		//scanf("%d", &pre_new);
		pre_new = no_show_num();
		stdin->_IO_read_ptr = stdin->_IO_read_end;//清残留换行			
		if(new_pwd == pre_new) {
			s_m->pwd = new_pwd;
			printf("修改成功！\n");
			return true;
		}
		else {
			printf("两次输入不一致，请重新输入！\n");
			goto in_new;
		}
	}
	if(0 == cnt)  {
		printf("您密码输入错误次数过多，已退出！\n");
		return false;
	}
	else goto in_old;
}

/*
 *在无效id中添加一个普通管理员
 *@m:普通管理员数组指针
 *@name:待添加姓名
 *@pwd:待添加密码
 *@station:待添加岗位
 */
void _add_manager(ManagerMessage* m,char* name, int pwd, int station) {
	for(int i=0; i<MAX_MANAGER_NUM; i++) {
		//该位置空时添加
		if(0 == m[i].id) {
			m[i].id = i+1;//id
			m[i].pwd = pwd;//密码
			strcpy(m[i].name, name);//姓名
			m[i].station = station; 
			manager_num++;
			break;		
		}
	}
}
/*
 *添加管理员
 */
bool add_manager(ManagerMessage* m) {
	debug("%s\n",__func__);
	
	if(manager_num >= MAX_MANAGER_NUM) {
		printf("普通管理员已满！\n");
		return false;	
	}
	//未满，添加
	char name[20] = {};
	int pwd = 0;
	int station = -1;
	
	printf("请输入管理员姓名：\n");
	GetString(name, MAX_NAME_NUM);//获取指定长度字符串
	printf("请输入管理员密码(4位有效数字)：\n");
	pwd = no_show_num();
	printf("请输入管理员岗位：\n");
	scanf("%d", &station);
	_add_manager(m, name, pwd, station);
	printf("添加成功！\n");
	return true;
}

/*根据id找下标*/
int _find_index_manager(ManagerMessage* m, int id) {
	int i = 0;
	if(id < 1) return -1;
	for(i; i<MAX_MANAGER_NUM; i++) {
		if(m[i].id == id) {
			return i;
		}
	}
	return -1;
}

/*
 *删除管理员 根据id删除
 */
bool del_manager(ManagerMessage* m) {
	debug("%s\n",__func__);
	int id = 0;//id为1时删除第一个
	char cmd = 0;//指令
	bool d_out = false;
	system("clear");//清屏幕
	/*
	printf("*可连续删除：\n");
	printf("*任意键继续：\n");
	printf("*键入 'q' 退出：\n");
	*/
	while(cmd != 'q') {
		printf("请输入需要删除的id：\n");
		scanf("%d",&id);
		stdin->_IO_read_ptr = stdin->_IO_read_end;//清除getch残留在输入缓冲区的换行
		
		int index = _find_index_manager(m, id);//获取待删除下标
		if(index < 0) {
			printf("无效id！\n");
		}else {
			m[index].id = 0;
			manager_num--;
			d_out = true;
			printf("已删除 id 为 %d 的管理员！\n",id);
		}
		printf("任意键继续...  q：退出\n");
		cmd = getch();
		stdin->_IO_read_ptr = stdin->_IO_read_end;//清除getch残留在输入缓冲区的换行
	}//while
	if(cmd == 'q') printf("正在退出！\n");
	stdin->_IO_read_ptr = stdin->_IO_read_end;//清除getch残留在输入缓冲区的换行
	return d_out;
}

/*根据id查找*/
void _id_find_show(ManagerMessage* m) {
	debug("%s\n",__func__);
	int id = 0,index = 0;
	printf("请输入需要查找的id：\n");
	scanf("%d",&id);
	index = _find_index_manager(m, id);
	
	if(index < 0) {
		printf("输入错误：id不在范围\n");
		return;
	}
	switch(m[index].station) {
		case 0: printf("id:%2d 姓名:%-4s 岗位:%s\n",m[index].id, m[id-1].name, "读者管理");break;
		case 1: printf("id:%2d 姓名:%-4s 岗位:%s\n",m[index].id, m[id-1].name, "图书管理");break;
		default : break;
	}
}
/*根据姓名查找*/
void _name_find_show(ManagerMessage* m) {
	debug("%s\n",__func__);
	char name[20] = {};
	int flag = 0;//查询标志位，1：有
	printf("请输入需要查找的姓名关键字：\n");
	GetString(name, MAX_NAME_NUM);
	for(int i=0; i<MAX_MANAGER_NUM; i++) {
		//名字存在且id有效
		if(strstr(m[i].name, name) && m[i].id) {
			flag = 1;
			switch(m[i].station) {
				case 0: printf("id:%2d 姓名:%-4s 岗位:%s\n",m[i].id, m[i].name, "读者管理");break;
				case 1: printf("id:%2d 姓名:%-4s 岗位:%s\n",m[i].id, m[i].name, "图书管理");break;
				default : break;
			}
		}
	}
	if(0 == flag) {
		printf("查询无果！\n");
	}
}
/*
 *查找管理员员
 */
void find_manager(ManagerMessage* m) {//传入结构体数组
	debug("%s\n",__func__);
	char num = 0;
	system("clear");
	puts("1.根据id查找");
	puts("2.根据姓名查找");
	puts("q.退出");
	while(1) {
		num = getch();
		switch(num) {
			case '1': _id_find_show(m);printf("请输入指令：\n");break;
			case '2': _name_find_show(m);printf("请输入指令：\n");break;
			case 'q': printf("正在退出！\n");return;
			default: printf("输入有误，请重新输入：\n");break;
		}
		stdin->_IO_read_ptr = stdin->_IO_read_end;//清缓冲区
	}
}

/*特殊排序处理，覆盖空位置进行显示*/
void manager_sort(ManagerMessage* m, int len) {
	for(int i=0; i<len-1; i++) {
		int min = i;//最小值下标
		for(int j=i+1; j<len; j++) {
			if(m[j].id < m[min].id) min = j;//获取最小id下标
		}
		//存入最小有效id
		if(min != i) {
			SWAP_INT(m[i].id, m[min].id);
			SWAP_INT(m[i].pwd, m[min].pwd);
			SWAP_S(m[i].name, m[min].name);
		}

	}
	int offset = MAX_MANAGER_NUM-manager_num;//无效id数量
	memmove(m, m+offset, sizeof(ManagerMessage)*manager_num);//覆盖无效位置
	memset(m+manager_num, 0, sizeof(ManagerMessage)*offset);//将末尾重复id清0
}
/*
 *分页显示管理员
 */
void show_manager(ManagerMessage* m) {
	debug("%s\n",__func__);
	int key = 0;
	int i = 0;//第一个管理员
	int div_num = MAX_MANAGER_NUM/PAGE_DIV;//每一页显示数量
	int page_num = MAX_MANAGER_NUM%PAGE_DIV ? PAGE_DIV+1 : PAGE_DIV;//总共页数
	int page = 1;//当前所在页
	int j = page*div_num;//第一页末尾
	ManagerMessage manager_show[MAX_MANAGER_NUM] = {};//用于排序显示已有管理员
	
	memcpy(manager_show, m, sizeof(ManagerMessage)*MAX_MANAGER_NUM);//拷贝数据
	//for(int i=0; i<MAX_MANAGER_NUM; i++) printf("%d ",manager_show[i].id);
	//puts("");
	manager_sort(manager_show, MAX_MANAGER_NUM);//将普通管理员按id排序放进 manager_show 数组显示
	//for(int i=0; i<MAX_MANAGER_NUM; i++) printf("%d ",manager_show[i].id);
	//分页循环显示 
	while(key != 'q') {
		system("clear");
		for(i; i<j && i<manager_num; i++) {//遍历每一页
			if(manager_show[i].id > 0) {
				switch(manager_show[i].station) {
					case 0: printf("id:%2d 姓名:%-4s 岗位:%s\n",manager_show[i].id, manager_show[i].name, "读者管理");break;
					case 1: printf("id:%2d 姓名:%-4s 岗位:%s\n",manager_show[i].id, manager_show[i].name, "图书管理");break;
					default : break;
				}	
			}	
		}
		printf("-------------%d---------------\n",page);
		printf("<--.上一页  -->.下一页  q.退出\n");
		key = getch();
		if(key == RIGHT)  {
			page++;//下一页
			if(page > page_num || manager_num <= div_num) {
				page = 1;//回到第一页
				i = 0;
			}
			j = page*div_num;//即将显示的页最后一个元素序号	
		}
		else if(key == LEFT) {
			page--;
			if(page < 1 && manager_num > div_num) {
				page = page_num;//去到最后一页
			}else page = 1;//只有1页数据时
			i = (page-1)*div_num;//即将显示的页第一个元素序号
			j = page*div_num;//即将显示的页最后一个元素序号
		}else {//其他键值处理,保持当前页不变
			i = (page-1)*div_num;
		}
		stdin->_IO_read_ptr = stdin->_IO_read_end;//清除getch残留在输入缓冲区的换行
	}//while
	printf("正在退出！\n");
	return ;
}
/*
 *批量增加文件中的管理员
 */
bool add_many_manager(ManagerMessage* m) {
	debug("%s\n",__func__);
	char file_self[256] = {};
	
	printf("请输入需要批量导入的文件：\n");
	scanf("%s",file_self);
	FILE* f_m = fopen(file_self,"r");//打开需要批量添加的管理员文件,自输入文件
	
	//FILE* f_m = fopen("./files/self_manager.txt","r");//打开需要批量添加的管理员文件
	if(NULL == f_m) {
		printf("查询不到此文件！\n");
		return false;
	}
	int cnt = 0;//添加成功个数
	if(manager_num >= MAX_MANAGER_NUM) {
		printf("管理员已满！\n");
		fclose(f_m);
		return false;
	}
	else {
		for(int i=0; i<MAX_MANAGER_NUM; i++) {
			if(m[i].id < 1) {
				//将文件中的管理员添加到空位置
				fscanf(f_m,"%s %d %d\n",m[i].name, &m[i].pwd, &m[i].station);
				m[i].id = i+1;
				manager_num++;//当前数量自增
				cnt++;
				if(manager_num >= MAX_MANAGER_NUM) {
					printf("管理员已满\n");
				}
			}
		}//for
		printf("成功添加 %d 个\n",cnt);
		fclose(f_m);
		return true;	
	}
}
/*
 *导出管理员信息为文本文件
 */
void export_manager(ManagerMessage* m) {
	debug("%s\n",__func__);
	char file_name[256] = {};
	printf("请输入需要导出到的文件：\n");
	scanf("%s",file_name);
	FILE* f_m = fopen(file_name, "w");
	//FILE* f_m = fopen("files/ManagerMessage.txt", "w");
	int ret = 0;
	for(int i=0; i<MAX_MANAGER_NUM; i++) {
		if(m[i].id > 0) {
			switch(m[i].station) {
				case 0: ret = fprintf(f_m, "id:%2d 姓名：%-4s 岗位：%s\n",m[i].id, m[i].name, "读者管理");break;
				case 1: ret = fprintf(f_m, "id:%2d 姓名：%-4s 岗位：%s\n",m[i].id, m[i].name, "图书管理");break;
				default : break;
			}
		}
		//printf("%d ",ret);	
	}
	printf("导出成功！\n");
	fclose(f_m);
	return ;
}


/*
 *载入普通管理员
 */
void load_file_manager(ManagerMessage* m) {
	int i = 0;//普通管理员下标
	FILE* f_manager = fopen("files/manager", "r");
	if(NULL == f_manager)  {
		f_manager = fopen("files/manager", "w");
	}
	//导入管理员文件所有数据
	while(fread(&m[i],1,sizeof(ManagerMessage),f_manager) && manager_num < MAX_MANAGER_NUM) {
		//有效普通管理员
		if(m[i].id > 0) {
			manager_num++;
		}
		i++;
	}
	fclose(f_manager);
}


/*
 *登录 主功能
 */
void login_super(SuperMessage* s_m, ManagerMessage* m) {
	char name[20] = {};//用户登录填入的姓名
	int pwd = 0;//用户登录填入的密码
	//超级管理员文件
	FILE* f_super = fopen("files/super", "r");
	//读取超级用户文件
	int ret_f = fread(s_m, 1, sizeof(SuperMessage), f_super);
	fclose(f_super);
	
	//载入普通管理员
	//load_file_manager(m);
	
in_name_pwd:	//超级管理员登录
	printf("请输入超级管理员用户名：\n");
	scanf("%s",name);
	stdin->_IO_read_ptr = stdin->_IO_read_end;//清残留换行
	printf("请输入超级管理员密码：\n");
	pwd = no_show_num();
	stdin->_IO_read_ptr = stdin->_IO_read_end;//清残留换行
	if(0 == strcmp(name, s_m->name)) {
		if(pwd == s_m->pwd) {
			printf("欢迎%s\n",s_m->name);
			//进入功能选择
			while(1) {
				sleep(1);//1s
				system("clear");
				menu();
				switch(getch()) {
					case '1': mod_pwd_super(s_m); break;
					case '2': add_manager(m); break;
					case '3': del_manager(m); break;
					case '4': find_manager(m); break;
					case '5': show_manager(m); break;
					case '6': add_many_manager(m); break;
					case '7': export_manager(m); break;
					case 'q': return;//结束
					default : break;
					
				}
				stdin->_IO_read_ptr = stdin->_IO_read_end;//清除getch残留在输入缓冲区的换行
				//break;//退出while
			}
			
		}else {//密码输入错误
			printf("用户名或密码输入错误！\n");
			goto in_name_pwd;
		}
	}else {//用户名出错
		printf("用户名或密码输入错误！\n");
		goto in_name_pwd;
	}
}

//超级管理员内存创建
SuperMessage* super_create() {
	SuperMessage* s_m = malloc(sizeof(SuperMessage));//获取超级管理员内存
	return s_m;
}
/*
 *初始化
 */
void load_super(SuperMessage* s_m, ManagerMessage* m) {
	FILE* f_super = fopen("files/super", "r");
	if(NULL == f_super) {//第一次登录
		f_super = fopen("files/super", "w");//新建文件
		char name[20] = {};
		int pwd = 0, pre_new = 0;
		printf("请设置超级管理员用户名：\n");
		scanf("%s",name);
in_pwd:
		stdin->_IO_read_ptr = stdin->_IO_read_end;//清缓冲区
		printf("请设置4位数字作为超级管理员密码：\n");
		//scanf("%d",&pwd);
		pwd = no_show_num();
		if(num_order(pwd) != 4) {
			printf("请输入4位有效数字作为密码！\n");
			goto in_pwd;
		}			
		printf("请确认您的密码：\n");
		//scanf("%d", &pre_new);
		pre_new = no_show_num();//验证密码
		if(pre_new == pwd) {
			printf("设置成功！");		
			//超级管理员赋值
			strcpy(s_m->name, name);
			s_m->pwd = pwd;
		}else {
			printf("两次输入的密码不一致，请重新输入！");
			goto in_pwd;
		}	
		//二进制方式写入文件
		fwrite(s_m, 1, sizeof(SuperMessage), f_super);
		fclose(f_super);
		//跳入加载项
		login_super(s_m, m);
	}
	else {
		//跳入加载项
		fclose(f_super);
		login_super(s_m, m);
	}
	//推出前保存所有数据至文件
	//save(s_m, m);
	return;
}

