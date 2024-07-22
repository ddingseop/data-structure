//2020111842 금명섭
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 이중 연결 리스트 노드 구조체
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// 이중 연결 리스트 구조체
typedef struct DoublyLinkedList {
    Node* header;
} DoublyLinkedList;

// 이중 연결 리스트 초기화 함수
void initialize(DoublyLinkedList* dll) { //헤더 노드
    dll->header = (Node*)malloc(sizeof(Node));
    dll->header->prev = dll->header;
    dll->header->next = dll->header;
}

// 정렬된 상태로 값 삽입 함수
void insert_sorted(DoublyLinkedList* dll, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value; //삽입할 값

    Node* current = dll->header->next; //현재노드를 리스트의 첫번째 노드로
    while (current != dll->header && current->data < value) { 
        //현재노드가 헤더노드가 아니고전값이 넣을 값보다 커지면 멈춤
        current = current->next; //이동
    }

    new_node->prev = current->prev; //새로넣을 노드의 prev
    new_node->next = current;
    current->prev->next = new_node;
    current->prev = new_node;
}

// 리스트 출력 함수
void print_forward(DoublyLinkedList* dll) {
    Node* current = dll->header->next; //첫번째 노드
    while (current != dll->header) {
        printf("[%d]", current->data);
        current = current->next;  //순차적으로 출력
    }
    printf("\n");
}

// 리스트 역순 출력 함수
void print_backward(DoublyLinkedList* dll) {
    Node* current = dll->header->prev;  //마지막 노드
    while (current != dll->header) {
        printf("[%d]", current->data);
        current = current->prev;  //역순으로 출력
    }
    printf("\n\n");
}

int main() {
    // 파일에서 정수 읽어오기
    FILE* file = fopen("in.txt", "r");
    int count;
    fscanf(file, "%d", &count);
    int* integers = (int*)malloc(count * sizeof(int));
    for (int i = 0; i < count; ++i) {
        fscanf(file, "%d", &integers[i]);
    }
    fclose(file);

    // 이중 연결 리스트 생성 후 정수 삽입
    DoublyLinkedList dll;
    initialize(&dll);
    for (int i = 0; i < count; ++i) {
        insert_sorted(&dll, integers[i]);
    }
    free(integers);

    // 초기 리스트 출력
    printf("print list:\n");
    print_forward(&dll);
    printf("print Inverse order:\n");
    print_backward(&dll);

    // 사용자 입력 및 처리
    int x;
    while (1) {
        printf("Input number: ");
        if (scanf("%d", &x) != 1) {
            printf("Invalid input. Please enter an integer.\n");
            while (getchar() != '\n'); // 입력 버퍼 비우기
            continue;
        }
        if (x < 0) {
            printf("Quit\n");
            break;
        }
        insert_sorted(&dll, x);
        printf("print list(%d inserted)\n", x);
        print_forward(&dll);
        printf("print inverse order\n");
        print_backward(&dll);
    }
}
