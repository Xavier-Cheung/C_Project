#include<stdio.h>
#include"swap.h"
int main()
{
    int a, b;
    int *aptr = &a, *bptr = &b;
    scanf("%d%d", &a, &b);
    swap(aptr, bptr);
    printf("a = %d\nb = %d\n", a, b);
}