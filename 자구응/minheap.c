#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define HEAP_FULL(n) (n == MAX - 1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
    char name[20];
    int number;
    int penalty;
} Student;

typedef struct {
    Student students[MAX];
    int size;
} MinHeap;

MinHeap heap;

void postorder(int index) {
    if (index <= heap.size) {
        postorder(index * 2); 
        postorder(index * 2 + 1); 
        printf("[%s,%d점] ", heap.students[index].name, heap.students[index].penalty);
    }
}

void push(Student item) {
    int i;
    i = ++heap.size;
    while ((i != 1) && (item.penalty < heap.students[i / 2].penalty)) {
        heap.students[i] = heap.students[i / 2]; 
        i /= 2; 
    }
    heap.students[i] = item;
}

Student pop() {
    int parent, child;
    Student item, temp;
    item = heap.students[1]; 
    temp = heap.students[heap.size--];
    parent = 1;
    child = 2;
    while (child <= heap.size) {
        if ((child < heap.size) && (heap.students[child].penalty > heap.students[child + 1].penalty))  
            child++;       
        if (temp.penalty <= heap.students[child].penalty)
            break;
        heap.students[parent] = heap.students[child];
        parent = child;
        child *= 2; 
    }
    heap.students[parent] = temp;
    return item;
}

int main() {
    FILE* fp = fopen("in.txt", "r");
    int n;
    fscanf(fp, "%d", &n);
    heap.size = 0;
    for (int i = 0; i < n; i++) {
        Student item;
        fscanf(fp, "%s %d %d", item.name, &item.number, &item.penalty);
        push(item);
    }
    fclose(fp);
    printf("Min heap (level order):\n");
    for (int i = 1; i <= heap.size; i++) {
        printf("[%s,%d점] ", heap.students[i].name, heap.students[i].penalty);
    }
    printf("\n\n");
    for (int i = 1; i < 5; i++) {
        Student reward = pop();
        printf("Delete #%d [%s,%d번,%d점]\n", i, reward.name, reward.number, reward.penalty);
    }
    printf("\n");
    printf("After deleting (postorder):\n");
    postorder(1);
    return 0;
}