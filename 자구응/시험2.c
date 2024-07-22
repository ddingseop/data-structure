#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node* left, * right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insertNode(struct Node* node, int data) {
    if (node == NULL) {
        return createNode(data);
    }

    if (data < node->data) {
        node->left = insertNode(node->left, data);
    }
    else if (data > node->data) {
        node->right = insertNode(node->right, data);
    }

    return node;
}

void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

struct Node* findLCA(struct Node* root, int a, int b) { 
    if (root == NULL) {
        return NULL;
    }

    if (root->data > a && root->data > b) {
        return findLCA(root->left, a, b);
    }

    if (root->data < a && root->data < b) {
        return findLCA(root->right, a, b);
    }

    return root;
}

int main() {
    FILE* file = fopen("in2.txt", "r");

    struct Node* root = NULL;
    int value;

    while (fscanf(file, "%d", &value) != EOF) {
        if (value < 0) {
            break;
        }
        root = insertNode(root, value);
    }
    fclose(file);

    printf("Inorder: ");
    inorderTraversal(root);
    printf("\n");

    int a, b;

    while (1) {
        printf("Input x, y: ");
        scanf("%d %d", &a, &b);
        if (a < 0 || b < 0) {
            break;
        }
        struct Node* lca = findLCA(root, a, b);
        if (lca != NULL) {
            printf("LCA(%d, %d): %d\n", a, b, lca->data);
        }
        else {
            printf("LCA(%d, %d): not found\n", a, b);
        }
    }

    return 0;
}
