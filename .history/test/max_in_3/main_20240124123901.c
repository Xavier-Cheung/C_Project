#include<stdio.h>

int max1_in_3(int x, int y, int z){
    if(x >= y && x >=z)
        return x;
    else if(y >= x && y >= z)
        return y;
    return z;
}

int max2_in_3(int x, int y, int z){
    int t = x > y ? x : y;
    return t > z ? t : z;
}

int main()
{
    int a, b, c;
    scanf("%d %d %d",&a, &b, &c);
    printf("%d", max1_in_3(a, b, c));
    printf("%d", max2_in_3(a, b, c));
    return 0;
}