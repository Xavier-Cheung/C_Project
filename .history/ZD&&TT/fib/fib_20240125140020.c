#include<stdio.h>

int fib(int n) {
    if(n == 0)
        return 0;
    else if(n == 1 || n == 2)
        return 1;
    else 
        return fib(n - 1) + fib(n - 2);
}

int main()
{
    int n;
    printf("请输入n: ");
    scanf("%d", &n);
    printf("第%d项斐波那契数为: %d", n, fib(n));
    return 0;
}