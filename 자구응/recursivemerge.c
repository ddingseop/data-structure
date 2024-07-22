//2020111842 ±Ý¸í¼·
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct {
    char name[100];
    int score;
} PERSON;


int listMerge(PERSON a[], int link[], int start1, int start2) {
    int last1, last2, lastResult = 0;
    for (last1 = start1, last2 = start2; last1 && last2;) {
        if (a[last1].score >= a[last2].score) {
            link[lastResult] = last1;
            lastResult = last1;
            last1 = link[last1];
        }
        else {
            link[lastResult] = last2;
            lastResult = last2;
            last2 = link[last2];
        }
    }
    if (last1 == 0) {
        link[lastResult] = last2;
    }
    else {
        link[lastResult] = last1;
    }
    return link[0];
}

int rmergeSort(PERSON a[], int link[], int left, int right) {
    if (left >= right) {
        return left;
    }
    int mid = (left + right) / 2;
    return listMerge(a, link, rmergeSort(a, link, left, mid), rmergeSort(a, link, mid + 1, right));
}

int main() {
    FILE* fp = fopen("in.txt", "r");
    int n;
    fscanf(fp, "%d", &n);
    PERSON* list = (PERSON*)malloc(sizeof(PERSON) * n);

    for (int i = 0; i < n; i++) {
        fscanf(fp, "%s %d", list[i].name, &list[i].score);
    }

    fclose(fp);

    PERSON a[MAX];
    int link[MAX] = { 0 };

    for (int i = 0; i < n; i++) {
        strcpy(a[i + 1].name, list[i].name);
        a[i + 1].score = list[i].score;
    }

    int sorted = rmergeSort(a, link, 1, n);

    printf("[Recursive merge sort]\n\n");

    for (int i = sorted; i != 0; i = link[i]) {
        printf("%5s: %4d\n", a[i].name, a[i].score);
    }

    free(list);
    return 0;
}

