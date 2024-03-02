#include<stdio.h>

int max1_in_3(int x, int y, int z){
    if(x >= y && x >=z)
        return x;
    else if(y >= x && y >= z)
        return y;
    return z;
}

int max2_in_3(int x, int y, int z){
    // int t = x > y ? x : y;
    // return t > z ? t : z;
    return (x > y ? x : y) > z ? (x > y ? x : y) : z;
}

int main()
{
    int a, b, c;
    scanf("%d %d %d",&a, &b, &c);
    printf("第一个函数：%d\n", max1_in_3(a, b, c));
    printf("第二个函数：%d\n", max2_in_3(a, b, c));
    return 0;
}