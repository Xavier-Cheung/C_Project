#include <stdio.h>
#include <stdlib.h>

typedef struct _tagDList {
    int data;
    struct _tagDList* pPre, *pNext;
} DLIST;

DLIST* createNode(int data) {
    DLIST* newNode = (DLIST*)malloc(sizeof(DLIST));
    newNode->data = data;
    newNode->pPre = newNode->pNext = NULL;
    return newNode;
}

void insertNode(DLIST** pHead, int data) {
    DLIST* newNode = createNode(data);
    if (*pHead == NULL) {
        *pHead = newNode;
    } else {
        newNode->pNext = *pHead;
        (*pHead)->pPre = newNode;
        *pHead = newNode;
    }
}

void deleteNode(DLIST** pHead, int num) {
    DLIST* current = *pHead;
    
    while (current != NULL) {
        DLIST* temp = current;
        current = current->pNext;

        if (temp->data == num) {
            if (temp->pPre != NULL) {
                temp->pPre->pNext = temp->pNext;
            } else {
                *pHead = temp->pNext;
            }

            if (temp->pNext != NULL) {
                temp->pNext->pPre = temp->pPre;
            }

            free(temp);
        }
    }
}

void printList(DLIST* pHead, FILE* outFile) {
    if (pHead == NULL) {
        fprintf(outFile, "-1\n");
        return;
    }

    while (pHead != NULL) {
        fprintf(outFile, "%d ", pHead->data);
        pHead = pHead->pNext;
    }

    fprintf(outFile, "\n");
}

int main() {
    FILE* inFile = fopen("dlistin.txt", "r");
    FILE* outFile = fopen("dlistout.txt", "w");

    int n;
    fscanf(inFile, "%d", &n);

    DLIST* pHead = NULL;
    int data;
    for (int i = 0; i < n; i++) {
        fscanf(inFile, "%d", &data);
        insertNode(&pHead, data);
    }

    int num;
    fscanf(inFile, "%d", &num);
    deleteNode(&pHead, num);

    printList(pHead, outFile);

    fclose(inFile);
    fclose(outFile);

    return 0;
}
