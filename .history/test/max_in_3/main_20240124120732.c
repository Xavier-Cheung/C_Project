#include<stdio.h>

int max_in_3(int x, int y, int z){
    if(x >= y && x >=z)
        return x;
    else if(y >= x && y >= z)
        return y;
    return z;
}

int main()
{
    int a, b, c;
    scanf("%d %d %d",&a, &b, &c);
    printf("%d", max_in_3(a, b, c));
    return 0;
}