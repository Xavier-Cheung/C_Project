#include<stdio.h>
#include"swap.h"
int main()
{
    int a = 1, b = 2;
    int *aptr = &a, *bptr = &b; 
    swap(aptr, bptr);
    printf("a = %d\nb = %d\n", a, b);
}