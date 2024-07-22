//2020111842 금명섭
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
} element;

void swap(element* a, element* b) {
    element temp = *a;
    *a = *b;
    *b = temp;
}

void adjust(element a[], int root, int n) {
    int child;
    element temp;
    temp = a[root];
    char* rootkey = a[root].key;
    child = 2 * root + 1;
    while (child < n) {
        if ((child < n - 1) && (strcmp(a[child].key, a[child + 1].key) > 0))
            child++; //둘 중 큰 노드 선택
        if (strcmp(rootkey, a[child].key) < 0)
            break;
        else { //child중 큰 노드를 부모로 옮김
            a[(child - 1) / 2] = a[child];
            child = 2 * child + 1;
        }
    }
    a[(child - 1) / 2] = temp;

}

void heapSort(element a[], int n) {
    for (int i = (n - 2) / 2; i >= 0; i--)
        adjust(a, i, n);

    for (int i = n - 1; i > 0; i--) {
        swap(&a[0], &a[i]);
        adjust(a, 0, i);
    }

}

int main() {
    char* arr[] = { "mercury","venus","earth","mars","jupiter","saturn","uranus","neptune","ceres","pluto","haumea","quaoar" };
    int n = sizeof(arr) / sizeof(arr[0]);
    element* elements = malloc(sizeof(element*) * n);
    for (int i = 0; i < n; i++) {
        elements[i].key = arr[i];
    }

    heapSort(elements, n);

    printf("[Heap sort]\n");
    for (int i = 0; i < n; i++) {
        printf("%s ", elements[i].key);
    }
    printf("\n");

    return 0;


}