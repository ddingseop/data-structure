//2020111842 금명섭
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 연결 리스트의 시작점을 가리키는 헤드 노드
Node* head = NULL;

// 새로운 노드를 생성하는 함수
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data; //해당노드의 데이터를 주어진 데이터로 설정
    newNode->next = NULL; //다음 노드를 가리키는 포인터 NULL로 초기화
    return newNode;
}

// 오름차순으로 연결 리스트에 노드를 삽입하는 함수
void insert(int data) {
    Node* newNode = createNode(data);

    // 리스트가 비어있거나 삽입할 값이 가장 작을 때
    if (head == NULL || head->data >= data) {
        newNode->next = head; //새로운 노드가 새로운 head를 가리키도록함
        head = newNode; //새로운 노드가 새로운 head가 됨
    }
    else {
        Node* current = head; //current 포인터를 사용하여 연결리스트 탐색
        while (current->next != NULL && current->next->data < data) {
            current = current->next; //
        }
        newNode->next = current->next; 
        current->next = newNode; 
    } // newNode가 current에 담기고 current->next가 다시 newNode를 가리키게 만듦
}

// 연결 리스트를 출력하는 함수
void printList() {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 연결 리스트에서 노드를 삭제하는 함수
void delete(int key) {
    Node* temp = head;
    Node* prev = NULL;

    // 삭제할 노드를 찾는 과정
    while (temp != NULL && temp->data != key) { //원하는 값을 찾을때까지
        prev = temp; //삭제할 노드의 이전노드를 알아야 해서 prev에 현재노드 할당
        temp = temp->next; //다음 노드로 이동
    }
    // 삭제할 노드가 없는 경우
    if (temp == NULL) {
        printf("%d가 리스트에 없음.\n", key);
        return;
    }
    // 삭제할 노드가 맨 앞에 있는 경우
    if (prev == NULL) {
        head = temp->next; //head를 삭제할노드(temp)의 다음 노드로 설정해서 첫번째 노드 건너뜀
    }
    else {
        prev->next = temp->next; //이전노드의 next를 temp의 다음노드로 설정해서 temp 건너뜀
    }

    free(temp);
}

int main() {
    FILE* fp = fopen("list3.txt", "r");
    int n,num;
    fscanf(fp, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%d ", &num);
        insert(num);
    }
    fclose(fp);

    printf("[오름차순 정렬]\n");
    printList();

    int deleteKey;
    while (1) {
        printf("삭제할 노드 번호: ");
        scanf("%d", &deleteKey);

        if (deleteKey < 0) {
            printf("종료");
            break;
        }
        // 입력받은 숫자를 연결 리스트에서 삭제
        delete(deleteKey);
        printList();
    }

    // 동적으로 할당된 메모리 해제
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    return 0;
}