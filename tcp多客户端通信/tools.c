#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"

//获取max_len-1个有效字符
int get_string(char buf[], int max_len) {
	stdin->_IO_read_ptr = stdin->_IO_read_end;//进来前先清缓冲区，防止上次残留
	int len = 0;
	fgets(buf, max_len, stdin);
	while(buf[len]) len++;//获取有效长度
	if(buf[len-1] && buf[len-1] == '\n') {//输入过短，\n接收进去了
		buf[len-1] = '\0';
		len--;//除去'\n'的实际个数
	}
	//过长时清缓冲区
	stdin->_IO_read_ptr = stdin->_IO_read_end;//清缓冲区
	return len;
}

