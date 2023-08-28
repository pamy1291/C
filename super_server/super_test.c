#include <stdio.h>
#include "superoper.h"

int main(int argc, char* argv[]) {
	//获取超级管理员内存
	s_m = super_create();
	//载入普通管理员
	load_file_manager(managers);
	//加载超级管理员功能
	load_super(s_m, managers);
	//数据保存
	save(s_m, managers);
	//销毁
	free(s_m);
	s_m = NULL;
	return 0;
}
