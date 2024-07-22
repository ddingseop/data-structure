//2020111842 ±Ý¸í¼·
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* LINK;
typedef struct node {
	int num;
	LINK next;
}NODE;

LINK appendNode(LINK head, LINK cur) {
	if (!head) {
		head = cur;
		return head;
	}
	cur->next = head;
	head = cur;
	return head;
}

void printList(LINK head) {
	LINK nextnode = head;
	while (nextnode) {
		printf("%d ", nextnode->num);
		nextnode = nextnode->next;
	}
}

LINK createNode(int number) {
	LINK cur = (NODE*)malloc(sizeof(NODE));
	cur->num = number;
	cur->next = NULL;
	return cur;
}

int main() {
	int n,num;
	FILE* fp;
	fp = fopen("list1.txt", "r");
	fscanf(fp, "%d", &n);
	LINK head = NULL, cur;
	for (int i = 0; i < n; i++) {
		fscanf(fp, "%d ", &num);
		cur = createNode(num);
		head = appendNode(head, cur);
	}
	printList(head);
	return 0;
}