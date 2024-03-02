#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void append(Node** head, char data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* lastNode = *head;
        while (lastNode->next != NULL) {
            lastNode = lastNode->next;
        }
        lastNode->next = newNode;
    }
}

void deleteSubList(Node** head, int start, int len) {
    Node *current = *head, *prev = NULL;
    int count = 1;
    while (current != NULL && count < start) {
        prev = current;
        current = current->next;
        count++;//找到起点
    }
    while (current != NULL && len > 0) {
        Node* temp = current;//逐个删除
        if (prev != NULL) {
            prev->next = current->next;
        } else {
            *head = current->next;
        }
        current = current->next;
        free(temp);
        len--;
    }
}

void insertListBefore(Node** dest, int pos, Node* src) {
    if (pos == 1) {
        Node* temp = src;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = *dest;
        *dest = src;
        return;
    }
    Node* current = *dest;
    int count = 1;
    while (current != NULL && count < pos - 1) {
        current = current->next;
        count++;
    }
    if (current != NULL) {
        Node* temp = src;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = current->next;
        current->next = src;
    }
}

void freeList(Node** head) {
    Node* current = *head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

void printListToFile(FILE* file, Node* head) {
    while (head != NULL) {
        fprintf(file, "%c", head->data);
        head = head->next;
    }
    fprintf(file, "\n");
}

// 打印链表
void printList(Node* node) {
    while (node != NULL) {
        printf("%c", node->data);
        node = node->next;
    }
}

int main() {
    FILE *inFile = fopen("listfunin.txt", "r");
    FILE *outFile = fopen("listfunout.txt", "w");
    int i, len, j;
    fscanf(inFile, "%d %d %d", &i, &len, &j);
    fgetc(inFile); // Read the newline character after the third integer

    Node *listA = NULL, *listB = NULL;
    char ch;

    // Build list A
    while ((ch = fgetc(inFile)) != '#') {
        if (ch != '\n' && ch != '\r') {
            append(&listA, ch);
            //printf("%c", ch);
        }
    }
    fgetc(inFile); // Read the newline character after list A

    // Build list B
    while ((ch = fgetc(inFile)) != '#') {
        if (ch != '\n' && ch != '\r') {
            append(&listB, ch);
            //printf("%c", ch);
        }
    }

    // Perform the operations
    deleteSubList(&listA, i, len);
    // printList(listA);
    // printList(listB);
    printListToFile(outFile, listA);
    insertListBefore(&listB, j, listA);
    // printList(listA);
    // printf("\n");
    // printList(listB);

    // Write results to the output file
    
    printListToFile(outFile, listB);

    // Free the lists
    freeList(&listB); // After merge, only listB needs to be explicitly freed

    fclose(inFile);
    fclose(outFile);

    return 0;
}
