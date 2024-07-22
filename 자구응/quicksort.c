//2020111842 ±Ý¸í¼·
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct element {
	char name[100];
	int key;
}element;

void quickSort(element a[], int left, int right) {
	int pivot, i, j;
	element temp;
	if (left < right) {
		i = left - 1, j = right;
		pivot = a[right].key;
		do {
			do i++; while (a[i].key > pivot);
			do j--; while (a[j].key < pivot);
			if (i < j) {
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		} while (i < j);
		temp = a[right];
		a[right] = a[i];
		a[i] = temp;

		printf("Pivot : %4d\n", pivot);
		quickSort(a, left, i - 1);
		quickSort(a, i + 1, right);
	}
}


int main(void) {
	FILE* fp1 = fopen("in1.txt", "r");
	FILE* fp2 = fopen("in2.txt", "r");
	FILE* fp3 = fopen("in3.txt", "r");
	int size1, size2, size3;
	fscanf(fp1, "%d", &size1);
	fscanf(fp2, "%d", &size2);
	fscanf(fp3, "%d", &size3);
	element* point1 = (element*)malloc(sizeof(element) * size1);
	element* point2 = (element*)malloc(sizeof(element) * size2);
	element* point3 = (element*)malloc(sizeof(element) * size3);

	for (int i = 0; i < size1; i++) {
		fscanf(fp1, "%s %d", &point1[i].name, &point1[i].key);
	}
	for (int i = 0; i < size2; i++) {
		fscanf(fp2, "%s %d", &point2[i].name, &point2[i].key);
	}
	for (int i = 0; i < size3; i++) {
		fscanf(fp3, "%s %d", &point3[i].name, &point3[i].key);
	}
	printf("[Quick sort]\n");
	quickSort(point1, 0, 11);
	for (int i = 0; i < size1; i++) {
		printf("   %5s:%4d\n", point1[i].name, point1[i].key);
	}

	printf("\n[Quick sort]\n");
	quickSort(point2, 0, 11);
	for (int i = 0; i < size1; i++) {
		printf("   %5s:%4d\n", point2[i].name, point2[i].key);
	}

	printf("\n[Quick sort]\n");
	quickSort(point3, 0, 11);
	for (int i = 0; i < size1; i++) {
		printf("   %5s:%4d\n", point3[i].name, point3[i].key);
	}

}