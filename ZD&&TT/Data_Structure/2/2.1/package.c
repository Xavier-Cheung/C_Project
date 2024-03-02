#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char parcelNumber[9]; // 快递单号
    char name[21];        // 收件人姓名
    char phoneNumber[12]; // 手机号
} Parcel;

// 比较函数，用于排序
int compare(const void *a, const void *b) {
    Parcel *parcelA = (Parcel *)a;
    Parcel *parcelB = (Parcel *)b;
    int phoneCompare = strcmp(parcelB->phoneNumber, parcelA->phoneNumber);
    if (phoneCompare == 0) { // 如果手机号相同，则按快递单号排序
        return strcmp(parcelA->parcelNumber, parcelB->parcelNumber);
    }
    return phoneCompare;
}

int main() {
    int n;
    printf("Enter the number of parcels: ");
    scanf("%d", &n);
    Parcel *parcels = (Parcel *)malloc(n * sizeof(Parcel));

    // 读取快递信息
    for (int i = 0; i < n; i++) {
        scanf("%s %s %s", parcels[i].parcelNumber, parcels[i].name, parcels[i].phoneNumber);
    }

    // 排序
    qsort(parcels, n, sizeof(Parcel), compare);

    // 输出排序后的信息
    for (int i = 0; i < n; i++) {
        printf("%10s %22s %12s\n", parcels[i].parcelNumber, parcels[i].name, parcels[i].phoneNumber);
    }

    // 释放内存
    free(parcels);

    return 0;
}
