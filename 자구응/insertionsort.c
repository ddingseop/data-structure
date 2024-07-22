//2020111842 금명섭
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    char name[20];
    int score;
} element;

void insert(element e, element a[], int i) {
    while (i >= 0 && e.score > a[i].score) {
        a[i + 1] = a[i];
        i--;
    }
    a[i + 1] = e;
}

void insertionSort(element a[], int n) {
    int j;
    for (j = 1; j < n; j++) {
        element temp = a[j];
        insert(temp, a, j - 1); //temp=insert할 element , j-1=현재 정렬된 사이즈
}

int main() {
    FILE* fp = fopen("in1.txt", "r");
    int n;
    fscanf(fp, "%d", &n);
    element a[MAX];

    for (int i = 0; i < n; i++) {
        fscanf(fp, "%s %d", a[i].name, &a[i].score);
    }
    fclose(fp);
    insertionSort(a, n);

    printf("[Insert sort]\n");
    for (int i = 0; i < n; i++) {
        printf("  %5s: %4d\n", a[i].name, a[i].score);
    }

    return 0;
}