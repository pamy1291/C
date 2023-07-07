#include <stdio.h>                                                          
#include <stdlib.h>
#include <time.h>

/*
 *n：随机 1-n 的数
 */
void rand_n(size_t n) {
    srand((unsigned int)time(NULL));//随机数种子
    for(int i=0; i<n; i++) {
        printf("%d ",1+rand()%(n));
    }
}

int main(int argc,const char* argv[]) {
    rand_n(5);//测试
    return 0;
}
