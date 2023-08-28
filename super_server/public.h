#ifndef PUBLIC_H
#define PUBLIC_H

#include <stdio.h>
#include <getch.h>

#define UP 183
#define DOWN 184
#define LEFT 186
#define RIGHT 185
#define BACK 127


//无回显数字
int no_show_num();
//限定输入个数及退格功能
int GetString(char buffer[], int maxLen);
//获取整形密码位数
int num_order(int num);
#endif
