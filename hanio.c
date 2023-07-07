include <stdio.h>

/*
 *n：层数(上到下)，A：起点，B：中转，C：终点
 */ 
void hanio(int n, char a, char b, char c) {
    if(n == 1) { 
        printf("%d层 from %c to %c\n",n, a, c);
    }
    else {
        hanio(n-1, a, c, b);//将n-1层放到b
        printf("%d层 from %c to %c\n",n, a, c);//最底层放到c
        hanio(n-1, b, a, c);//n-1层从b放到c
    }
}

int main(int argc,const char* argv[])
{
    int n;
    printf("请输入层数：");
    scanf("%d",&n);
    hanio(n, 'A', 'B', 'C');
    return 0;
}     
