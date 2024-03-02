#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 20

typedef struct Node {
    char data;
    struct Node* left;
    struct Node* right;
} Node;

Node* buildTree(char preorder[], char inorder[], int preStart, int preEnd, int inStart, int inEnd) {
    if (preStart > preEnd || inStart > inEnd) {
        return NULL;
    }

    char rootValue = preorder[preStart];
    Node* root = (Node*)malloc(sizeof(Node));
    root->data = rootValue;
    root->left = root->right = NULL;

    int rootIndex;
    for (rootIndex = inStart; rootIndex <= inEnd; rootIndex++) {
        if (inorder[rootIndex] == rootValue) {
            break;
        }
    }

    int leftSubtreeSize = rootIndex - inStart;

    root->left = buildTree(preorder, inorder, preStart + 1, preStart + leftSubtreeSize, inStart, rootIndex - 1);
    root->right = buildTree(preorder, inorder, preStart + leftSubtreeSize + 1, preEnd, rootIndex + 1, inEnd);

    return root;
}

void postorderTraversal(Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%c", root->data);
    }
}

int main() {
    char preorder[MAX_NODES];
    char inorder[MAX_NODES];

    printf("Enter the preorder traversal sequence: ");
    scanf("%s", preorder);

    printf("Enter the inorder traversal sequence: ");
    scanf("%s", inorder);

    int len = strlen(preorder);

    Node* root = buildTree(preorder, inorder, 0, len - 1, 0, len - 1);

    printf("Postorder traversal sequence: ");
    postorderTraversal(root);
    printf("\n");

    return 0;
}
