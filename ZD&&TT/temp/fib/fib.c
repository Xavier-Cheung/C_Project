#include<stdio.h>
#include<math.h>

long long fib1(int n) {//递归方法
    if(n == 0)
        return 0;
    else if(n == 1 || n == 2)
        return 1;
    else 
        return fib1(n - 1) + fib1(n - 2);
}

long long fib2(int n) {//迭代法
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	long long a = 0;
	long long b = 1;
	long long c = 1;
	while (n - 2)
	{
		a = b;
		b = c;
		c = a + b;
		n--;
	}
	return c;
}

long long fib3(int n) {
    double sqrt5 = sqrt(5);
    double fibN = pow((1 + sqrt5) / 2, n) - pow((1 - sqrt5) / 2, n);
    return round(fibN / sqrt5);
}


int main()
{
    int n;
    printf("请输入n: ");
    scanf("%d", &n);

    printf("fib1: 第%d项斐波那契数为: %lld\n", n, fib1(n));
    printf("fib2: 第%d项斐波那契数为: %lld\n", n, fib2(n));
    printf("fib3: 第%d项斐波那契数为: %lld\n", n, fib3(n));
    
    return 0;
}