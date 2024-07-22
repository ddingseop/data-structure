//2020111842 ±Ý¸í¼·
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    int score;
} element;

void merge(element arr[], element temp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (arr[i].score >= arr[j].score) {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (int i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}

void rmergeSort(element arr[], element temp[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        rmergeSort(arr, temp, left, mid);
        rmergeSort(arr, temp, mid + 1, right);
        merge(arr, temp, left, mid, right);
    }
}

int main() {
    FILE* fp = fopen("in.txt", "r");
    int n;
    fscanf(fp, "%d", &n);

    element* arr = (element*)malloc(n * sizeof(element));
    element* temp = (element*)malloc(n * sizeof(element));

    for (int i = 0; i < n; i++) {
        fscanf(fp, "%s %d", arr[i].name, &arr[i].score);
    }

    fclose(fp);

    rmergeSort(arr, temp, 0, n - 1);

    printf("[Recursive merge sort]\n\n");
    for (int i = 0; i < n; i++) {
        printf("%5s: %4d\n", arr[i].name, arr[i].score);
    }

    free(arr);
    free(temp);

    return 0;
}