//2020111842 금명섭
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct Node* insert(struct Node* node, int key) {
    if (!node) {
        return createNode(key);
    }
    if (key < node->key) { //넣을 키값이 루트의 키값보다 작으면
        node->left = insert(node->left, key); //왼쪽
    }
    else if (key > node->key) { //넣을 키값이 루트의 키값보다 크면
        node->right = insert(node->right, key); //오른쪽
    }
    return node;
}

void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

struct Node* modifiedSearch(struct Node* node, int k) { //node=루트노드, k=찾고자 하는 키값
    if (node == NULL || node->key == k) {
        return node; //재귀하다가 같은 값이면 리턴
    }
    if (k < node->key) {
        return modifiedSearch(node->left, k); //왼쪽자식노드에서부터 재귀
    }
    else {
        return modifiedSearch(node->right, k); //오른쪽자식노드에서부터 재귀
    }
}

void search(struct Node* root, int key) {
    struct Node* result = modifiedSearch(root, key);
    if (result != NULL)
        printf("%3d : 있음\n", key);
    else
        printf("%3d : 없음\n", key);
}

struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL)
        current = current->left; //가장 왼쪽 노드까지 감
    return current;
}

struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) return root;
    //지울 키값과 현재노드의 키값 비교
    if (key < root->key) //지울 값이 현재노드의 키값보다 작으면 왼쪽 탐색
        root->left = deleteNode(root->left, key); 
    else if (key > root->key) //보다 크면 오른쪽 탐색
        root->right = deleteNode(root->right, key);
    else { //삭제할 노드를 찾았다면
        if (root->left == NULL) { //왼쪽 자식이 없는 경우
            struct Node* temp = root->right; //temp에 현재노드의 오른쪽 자식을 저장하고
            free(root); //현재노드 해제
            return temp; //temp는 삭제된 노드(root)의 부모노드가 가리키는 자식노드로 설정
        }
        else if (root->right == NULL) { //오른쪽 자식이 없는 경우
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        //자식이 둘다 있는 경우
        struct Node* temp = minValueNode(root->right); //루트노드의 오른쪽 자식중에서 가장왼쪽 노드
        root->key = temp->key; //현재노드의 키 값을 오른쪽 서브트리에서 찾은 가장 작은 값(temp->key)으로 대체
        root->right = deleteNode(root->right, temp->key); //오른쪽 서브트리에서 temp->key 값을 가진 노드를 삭제합니다
    }
    return root;
}

int main() {
    FILE* fp1, * fp2;
    fp1 = fopen("in.txt", "r");
    fp2 = fopen("search.txt", "r");

    int n, key;
    struct Node* root = NULL;


    fscanf(fp1, "%d", &n);
    while (n--) {
        fscanf(fp1, "%d", &key);
        root = insert(root, key);
    }


    printf("[Inorder traversal]\n");
    inorder(root);
    printf("\n\n");


    fscanf(fp2, "%d", &n); 
    while (fscanf(fp2, "%d", &key) != EOF) {
        search(root, key);
    }

    while (1) {
        printf("\n삭제할 노드 : ");
        scanf("%d", &key);
        if (key == -1) {
            printf("Quit.\n");
            break;
        }
        struct Node* nodeToDelete = modifiedSearch(root, key);
        if (nodeToDelete != NULL) {
            root = deleteNode(root, key);
            inorder(root);
        }
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}