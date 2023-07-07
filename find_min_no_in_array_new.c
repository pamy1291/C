#include <stdio.h>                                                               

int main(int argc,const char* argv[])
{
    int N = 0;
    printf("请输入N的值：");
    scanf("%d",&N);
    int arr1[N],arr2[N];
    for(int i=0; i<N; i++) {
        scanf("%d",&arr1[i]);
        arr2[i] = 0;
    }   
    for(int i=0; i<N; i++) {
        if(1 <= arr1[i]  && arr1[i] <= N) {
            arr2[arr1[i]-1] = 1;//将arr1中出现的正整数-1作为下标在arr2中作标记
        }
    }
    int i;
    for(i=0; i<N; i++) {
        if(0 == arr2[i]) {//arr中为出现的正整数
            break;
        }
    }    
    printf("%d\n",i+1);
    return 0;
}       
