#include<stdio.h>
#include<string.h>

void abbreviate(char *str) {
    int len = strlen(str);//获得字符串的长度

    int i, start = 0, count = 1;//i用来遍历字符串表示每个字符的下标
                                //start表示升序字符串的起点
                                //count用来统计升序字符串的长度

    for (i = 1; i <= len; i++) {//从下标为1处开始判断
        if (str[i] == str[i - 1] + 1) {
            count++;//如果升序，则长度加一
        } 
        else {//如果不是升序，则说明需要判断输出方式
            if (count >= 3) //长度大于2，则需要缩写，输出起点和终点的字符和‘-’
                printf("%c-%c", str[start], str[i - 1]);
            else //否则长度为1或者2，正常输出字符即可
                for (int j = start; j < i; j++) 
                    printf("%c", str[j]);
            //输出完成代表一段升序字符串处理结束，在处理接下来的字符串前要默认count为1，起点为i(即上一个结束的后一位)
            start = i;
            count = 1;
        }
    }
}

int main()
{
    char str[102];

    printf("请输入一行字符串：\n");
    fgets(str, 102, stdin);//输入字符串
    
    abbreviate(str);//调用函数

    return 0;
}