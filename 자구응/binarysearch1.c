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
	if (key < node->key) { //삽입할 값이 현재노드의 키 값보다 작으면 
		node->left = insert(node->left, key); //왼쪽에 삽입
	}
	else if (key > node->key) { //삽입할 값이 현재노드의 키 값보다 크면
		node->right = insert(node->right, key); //오른쪽에 삽입
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
	if (node == NULL || node->key == k) { //키를 찾았으면
		return node; //반환하기
	}
	if (k < node->key) { //찾을 값이 현재노드의 키값보다 작으면
		return modifiedSearch(node->left, k); //왼쪽 자식으로 이동
	}
	else { //찾을 값이 현재노드의 키값보다 크면 
		return modifiedSearch(node->right, k); //오른쪽으로 이동
	}
}

void search(struct Node* root, int key) {
	struct Node* result = modifiedSearch(root, key);
	if (result != NULL)
		printf("%3d : 있음\n", key);
	else
		printf("%3d : 없음\n", key);
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