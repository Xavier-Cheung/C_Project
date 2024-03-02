#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 创建新节点
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(1); // 如果内存分配失败，则退出程序
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 在链表头部插入节点
void insertAtHead(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

// 删除链表中的一个节点
void deleteNode(Node** head, int key) {
    Node *temp = *head, *prev = NULL;
    // 如果头节点本身就是要删除的节点
    if (temp != NULL && temp->data == key) {
        *head = temp->next; // 改变头指针
        free(temp); // 释放旧的头节点
        return;
    }
    // 查找要删除的节点
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }
    // 如果key不存在于链表中
    if (temp == NULL) return;
    // 从链表中删除节点
    prev->next = temp->next;
    free(temp); // 释放内存
}

// 打印链表
void printList(Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}

int main() {
    Node* head = NULL;
    int num;
    while (1) {
        scanf("%d", &num);
        if (num == -1) break;
        insertAtHead(&head, num);
    }
    scanf("%d", &num); // 读取要删除的整数
    deleteNode(&head, num); // 删除节点
    printList(head); // 打印链表
    return 0;
}
