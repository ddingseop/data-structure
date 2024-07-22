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
	if (key < node->key) { //������ ���� �������� Ű ������ ������ 
		node->left = insert(node->left, key); //���ʿ� ����
	}
	else if (key > node->key) { //������ ���� �������� Ű ������ ũ��
		node->right = insert(node->right, key); //�����ʿ� ����
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

struct Node* modifiedSearch(struct Node* node, int k) {
	if (node == NULL || node->key == k) { //Ű�� ã������
		return node; //��ȯ�ϱ�
	}
	if (k < node->key) { //ã�� ���� �������� Ű������ ������
		return modifiedSearch(node->left, k); //���� �ڽ����� �̵�
	}
	else { //ã�� ���� �������� Ű������ ũ�� 
		return modifiedSearch(node->right, k); //���������� �̵�
	}
}

void search(struct Node* root, int key) {
	struct Node* result = modifiedSearch(root, key);
	if (result != NULL)
		printf("%3d : ����\n", key);
	else
		printf("%3d : ����\n", key);
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
	fclose(fp1);
	fclose(fp2);
	return 0;
}