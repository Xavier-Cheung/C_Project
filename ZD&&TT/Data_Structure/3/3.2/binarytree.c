#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* insertNode(Node* root, int value) {
    if (root == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = value;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (value < root->data) {
        root->left = insertNode(root->left, value);
    } else if (value > root->data) {
        root->right = insertNode(root->right, value);
    }

    return root;
}

Node* findMin(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Node* deleteNode(Node* root, int value) {
    if (root == NULL) {
        return root;
    }

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%4d", root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    Node* root = NULL;
    int value;

    printf("Enter integers to build a binary search tree (-1 to end input):\n");
    while (1) {
        scanf("%d", &value);
        if (value == -1) {
            break;
        }
        root = insertNode(root, value);
    }

    printf("Enter a value to delete: ");
    scanf("%d", &value);
    root = deleteNode(root, value);

    printf("Inorder traversal after deletion:\n");
    if (root == NULL) {
        printf("-1\n");
    } else {
        inorderTraversal(root);
        printf("\n");
    }

    return 0;
}
