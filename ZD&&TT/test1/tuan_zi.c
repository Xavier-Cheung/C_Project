#include <stdio.h>
void fun(int* x,int* y)
{
    if(*x>*y){
        *y = *x ;
    }
}
int main()
{
    int a,b,c;
    scanf("%d%d%d",&a,&b,&c) ;
    int *a_ptr = &a;
    int *b_ptr = &b;
    int *c_ptr = &c;
    fun(a_ptr,b_ptr);
    fun(b_ptr,c_ptr);
    fun(a_ptr,c_ptr);
    printf("%d",c);
    return 0 ;

}
