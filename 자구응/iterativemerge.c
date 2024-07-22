//2020111842 ±Ý¸í¼·
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[100];
    int score;
} PERSON;

void merge(PERSON* initList, PERSON* mergedList, int i, int m, int n) {
    int j, k, t;
    j = m + 1;
    k = i;

    while (i <= m && j <= n) {
        if (initList[i].score >= initList[j].score) {
            mergedList[k++] = initList[i++];
        }
        else {
            mergedList[k++] = initList[j++];
        }
    }

    while (i <= m) {
        mergedList[k++] = initList[i++];
    }

    while (j <= n) {
        mergedList[k++] = initList[j++];
    }

    for (i = i; i <= n; i++) {
        initList[i] = mergedList[i];
    }
}

void mergePass(PERSON* initList, PERSON* mergedList, int n, int s) {
    int i;
    for (i = 0; i <= n - 2 * s; i += 2 * s) {
        merge(initList, mergedList, i, i + s - 1, i + 2 * s - 1);
    }
    if (i + s < n) {
        merge(initList, mergedList, i, i + s - 1, n - 1);
    }
    else {
        for (int j = i; j < n; j++) {
            mergedList[j] = initList[j];
        }
    }
}

void mergeSort(PERSON* initList, int n) {
    PERSON* mergedList = (PERSON*)malloc(sizeof(PERSON) * n);
    int s = 1;
    while (s < n) {
        printf("    s: %2d\n", s);
        mergePass(initList, mergedList, n, s);
        s *= 2;
        mergePass(mergedList, initList, n, s);
        s *= 2;
    }
    printf("\n");
    free(mergedList);
}

int main() {
    FILE* fp = fopen("in.txt", "r");
    int n;
    fscanf(fp, "%d", &n);
    PERSON* initList = (PERSON*)malloc(sizeof(PERSON) * n);

    for (int i = 0; i < n; i++) {
        fscanf(fp, "%s %d", initList[i].name, &initList[i].score);
    }
    fclose(fp);

    printf("[Iterative merge sort]\n\n");
    mergeSort(initList, n);

    for (int i = 0; i < n; i++) {
        printf("%5s: %4d\n", initList[i].name, initList[i].score);
    }

    free(initList);
    return 0;
}
