// #include <stdio.h>
// #include<math.h>

// int isPrime(int n) {
//     if(n == 1 || n == 0)
//         return 0;
//     if(n == 2)
//         return 1;
//     for(int i = 2; i <= sqrt(n); i++) {
//         if(n % i == 0) {
//             return 0;
//         }
//     }
//     return 1;
// }

// void primeFactorization(int n) {
//     printf("%d=", n);
//     if(isPrime(n)){
//         printf("%d*1", n);
//         return;
//     }
//     int i = n - 1;
//     while(n != 1) {
//         if(n % i == 0 && isPrime(i)) {
//             printf("%d", i);
//             n /= i;
//             if(n != 1)
//                 printf("*");
//         }
//         else
//             i--;
//     }
//     printf("\n");    
// }

// int main() {
//     int num;
    
//     printf("请输入一个正整数：\n");
//     scanf("%d", &num);
    
//     primeFactorization(num);
    
//     return 0;
// }

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void primeFactorization(int n, int* factors, int* count) {
    for (int i = 2; i <= sqrt(n); ++i) {
        while (n % i == 0) {
            factors[(*count)++] = i; // 存储质因数
            n /= i;
        }
    }
    if (n > 1) {
        factors[(*count)++] = 1;
        factors[(*count)++] = n; // 如果n为质数，则直接存储
    }
}

int main() {
    int num;
    printf("请输入一个正整数：\n");
    scanf("%d", &num);

    int* factors = (int*)malloc(sizeof(int) * num); // 分配足够大的空间来存储所有可能的质因数
    int count = 0; // 质因数的数量

    primeFactorization(num, factors, &count);

    printf("%d=", num);
    for (int i = count - 1; i >= 0; --i) { // 逆序输出
        printf("%d", factors[i]);
        if (i > 0) {
            printf("*");
        }
    }
    printf("\n");

    free(factors); // 释放分配的空间

    return 0;
}
