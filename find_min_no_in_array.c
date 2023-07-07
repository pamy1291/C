#include <stdio.h>

int main(int argc,const char* argv[])
{
    int n = 0;
    int max;//可出现的最大正整数，用于遍历
    int min;//数组中未出现最小正整数
    int temp;//临时变量
    int flag = 0;//全为负数
    printf("请输入数组个数：");
    scanf("%d",&n);                                                             
    int a[n];
    max = n+2;//n+1为最大结果
    min = n+1;
    temp = n+1;
    printf("请输入数组数据，空格隔开：");
    for(int i=0; i<n; i++) {
        scanf("%d", &a[i]);
    }
    for(int i=0; i<n; i++) {
        if(a[i] < max && a[i] >= 0) {
            flag = 1;
            if( ((a[i] + 1) < temp) && ((a[i] + 1) < min) ) {
                min = a[i] + 1;
                flag = 1;
            }
            if(a[i+1] == min) {//下一个与最小正整数相等时重置
                min = n+1;
            }
        }
    }
    if(0 == flag) {//数组数全为负数的处理
        min = 1;
    }
    printf("未出现的最小正整数为：%d",min);
    return 0;
}     
