#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void countingSort(int array[], int size, int place) {
    int* output = (int*)malloc(size * sizeof(int));
    int max = 10;
    int count[10] = { 0 };

    for (int i = 0; i < size; i++)
        count[(array[i] / place) % 10]++;

    for (int i = 1; i < max; i++)
        count[i] += count[i - 1];

    for (int i = size - 1; i >= 0; i--) {
        output[count[(array[i] / place) % 10] - 1] = array[i];
        count[(array[i] / place) % 10]--;
    }

    for (int i = 0; i < size; i++)
        array[i] = output[i];

    free(output);
}

void radixSort(int array[], int size) {

    int max = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] > max)
            max = array[i];
    }

    for (int place = 1; max / place > 0; place *= 10)
        countingSort(array, size, place);
}

int main() {
    int size, range;

    printf("Input size: ");
    scanf("%d", &size);
    printf("Input range (10~999): ");
    scanf("%d", &range);

    if (range < 10 || range > 999) {
        printf("Invalid range. Please enter a range between 10 and 999.\n");
        return 1;
    }

    int* array = (int*)malloc(size * sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    srand(time(0));

    for (int i = 0; i < size; i++) {
        array[i] = (rand() % range) + 1;
    }

    printf("[Before radix sort] ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    radixSort(array, size);

    for (int i = 0; i < size / 2; i++) {
        int temp = array[i];
        array[i] = array[size - i - 1];
        array[size - i - 1] = temp;
    }

    printf("[After radix sort] ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);

    return 0;
}
