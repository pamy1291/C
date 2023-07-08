#include <stdio.h>
#include <stdlib.h>

size_t s_strlen(const char  *s) { //计算字符串长度
    const char* temp = s;
    while(*temp) temp++;
    return temp - s;
}
char* s_strcpy(char *dest, const char *src) { //拷贝字符
    char* temp = dest;
    while(*temp++ = *src++);
    return dest;
}
char* s_strcat(char *dest, const char *src) { //追加字符
    char* temp = dest;
    while(*temp) temp++;
    while(*temp++ = *src++);
    return dest;
}
int s_strcmp(const char *s1, const char *s2) { //比较字符大小
    while(*s1 && *s1 == *s2) s1++,s2++;
    //return *s1 - *s2;                                                         
    if(*s1 > *s2) return 1;
    if(*s1 == *s2) return 0;
    if( *s1 < *s2) return -1;

}

int main(int argc,const char* argv[])
{
    char s1[] = "aaaa", s2[] = "aab";
    char *str = malloc(20);
    str = "world hello!";
    printf("cat = %d\n", s_strlen(str));
    printf("cpydest=%s\n",s_strcpy(s1, s2));
    printf("catdest=%s\n",s_strcat(s2, "ss"));
    printf("比较大小：%d\n",s_strcmp(s2, "abb"));
    return 0;
}      
