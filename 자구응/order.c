#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* Binary_tree(int x) {
    if (x > 100) {
        return NULL;
    }
    struct Node* root = createNode(x);
    root->left = Binary_tree(x * 3);
    root->right = Binary_tree(x * 4);
    return root;
}

void Inorder(struct Node* root) { //LVR
    if (root != NULL) {
        Inorder(root->left);
        printf("%d ", root->data);
        Inorder(root->right);
    }
}

void Postorder(struct Node* root) { //LRV
    if (root != NULL) {
        Postorder(root->left);
        Postorder(root->right);
        printf("%d ", root->data);
    }
}

void Preorder(struct Node* root) { //VLR
    if (root != NULL) {
        printf("%d ", root->data);
        Preorder(root->left);
        Preorder(root->right);
    }
}

int main() {
    int x;
    while (1) {
        printf("input data:");
        scanf("%d", &x);
        if (x < 0) {
            printf("Á¾·á\n");
            break;
        }
        printf("\n");
        struct Node* root = Binary_tree(x);
        printf("Inorder: ");
        Inorder(root);
        printf("\nPostorder: ");
        Postorder(root);
        printf("\nPreorder: ");
        Preorder(root);
        printf("\n\n");
    }
    return 0;
}
