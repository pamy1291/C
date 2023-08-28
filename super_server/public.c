#include "public.h"

//获取整形密码位数
int num_order(int num) {
	int cnt = 1;
	while(num/10) {
		cnt++;
		num/=10;
	}
	return cnt;
}

//从屏幕输入，返回不回显的数字，getch()的扩展
int no_show_num() {
	int pwd = 0;
	int i = 0;
	int key;
	while( (key = getch()) != '\n') {
		//stdin->_IO_read_ptr = stdin->_IO_read_end;//清缓冲区
		if(key == BACK) {//退格
			if(i > 0) { 
				i--;
				putchar('\b');
				putchar(' ');
				putchar('\b');
				pwd /= 10;
			}
			continue;
		}
		//按位转整形
		pwd = pwd*10 + (key-'0');
		printf("*");
		i++;
	}
	printf("\n");
	stdin->_IO_read_ptr = stdin->_IO_read_end;//清缓冲区
	return pwd;
}

/*
 *限定输入个数及退格功能
 *@buffer[]:接收字符数组
 *@maxLen:最大有效长度
 */
int GetString(char buffer[], int maxLen) {
	int cnt=0;
	int readch;
	while( (readch=getch()) != '\n' ) {	
		stdin->_IO_read_ptr = stdin->_IO_read_end;//清缓冲区
		if(readch == BACK) {//退格
			if(cnt > 0) { 
				cnt--;
				putchar('\b');
				putchar(' ');
				putchar('\b');
			}
			continue;
		}

		//限制左右键
		if(readch == LEFT || readch == RIGHT) {
			getch();
			continue;
		}
		//回显
		if(cnt < maxLen) putchar(readch);
		else continue;

		buffer[cnt++] = readch;//赋值合法字符
	}
	printf("\n");
	if(cnt < maxLen) buffer[cnt] = 0;//输入数量小于最大时，最后一位置空
	return cnt;
}
