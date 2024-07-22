//2020111842 �ݸ�
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
    if (key < node->key) { //���� Ű���� ��Ʈ�� Ű������ ������
        node->left = insert(node->left, key); //����
    }
    else if (key > node->key) { //���� Ű���� ��Ʈ�� Ű������ ũ��
        node->right = insert(node->right, key); //������
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

struct Node* modifiedSearch(struct Node* node, int k) { //node=��Ʈ���, k=ã���� �ϴ� Ű��
    if (node == NULL || node->key == k) {
        return node; //����ϴٰ� ���� ���̸� ����
    }
    if (k < node->key) {
        return modifiedSearch(node->left, k); //�����ڽĳ�忡������ ���
    }
    else {
        return modifiedSearch(node->right, k); //�������ڽĳ�忡������ ���
    }
}

void search(struct Node* root, int key) {
    struct Node* result = modifiedSearch(root, key);
    if (result != NULL)
        printf("%3d : ����\n", key);
    else
        printf("%3d : ����\n", key);
}

struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL)
        current = current->left; //���� ���� ������ ��
    return current;
}

struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) return root;
    //���� Ű���� �������� Ű�� ��
    if (key < root->key) //���� ���� �������� Ű������ ������ ���� Ž��
        root->left = deleteNode(root->left, key); 
    else if (key > root->key) //���� ũ�� ������ Ž��
        root->right = deleteNode(root->right, key);
    else { //������ ��带 ã�Ҵٸ�
        if (root->left == NULL) { //���� �ڽ��� ���� ���
            struct Node* temp = root->right; //temp�� �������� ������ �ڽ��� �����ϰ�
            free(root); //������ ����
            return temp; //temp�� ������ ���(root)�� �θ��尡 ����Ű�� �ڽĳ��� ����
        }
        else if (root->right == NULL) { //������ �ڽ��� ���� ���
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        //�ڽ��� �Ѵ� �ִ� ���
        struct Node* temp = minValueNode(root->right); //��Ʈ����� ������ �ڽ��߿��� ������� ���
        root->key = temp->key; //�������� Ű ���� ������ ����Ʈ������ ã�� ���� ���� ��(temp->key)���� ��ü
        root->right = deleteNode(root->right, temp->key); //������ ����Ʈ������ temp->key ���� ���� ��带 �����մϴ�
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
        printf("\n������ ��� : ");
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