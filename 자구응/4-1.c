//2020111842 금명섭
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
	int I, J, K;
	printf("A[I][J][K]...\n");
	printf("Input I:");
	scanf("%d", &I);
	printf("Input J:");
	scanf("%d", &J);
	printf("Input K:");
	scanf("%d", &K);
	//3차원배열 동적할당
	int*** A;
	A = (int***)malloc(sizeof(**A) * I);
	for (int i = 0; i < I; i++) {
		A[i] = (int**)malloc(sizeof(int*) * J);
		for (int j = 0; j < J; j++) {
			A[i][j] = (int*)malloc(sizeof(int) * K);
		}
	}
	
	//배열에 값넣고 출력하기
	for (int i = 0; i < I; i++) {
		for (int j = 0; j < J; j++) {
			for (int k = 0; k < K; k++) {
				A[i][j][k] = i + j + k;
				printf("A[%d][%d][%d]=%d ", i,j,k,A[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}
	//반대순서로 해제하기
	for (int i = 0; i < I; i++) {
		for (int j = 0; j < J; j++) {
			free(A[i][j]);
		}
		free(A[i]);
	}
	free(A);
	return 0;
}