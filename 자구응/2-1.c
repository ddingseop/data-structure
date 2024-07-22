//2020111842 금명섭
#include <stdio.h>
#include <time.h>
#define MAX_SIZE 1001
#define _CRT_SECURE_NO_WARNINGS
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
void sort(int[], int);

void main(void) {
	int i, n, step = 10;
	int a[MAX_SIZE];
	double duration; //실행시간
	clock_t start;  //시간 측정 변수
	printf("    n   time\n");
	for (n = 0; n <= 1000; n += step) {
		for (i = 0; i < n; i++) {
			a[i] = n - i; //배열 초기화
		}
		start = clock(); //정렬 시작 시간 기록
		sort(a, n); //정렬하기
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC; //정렬 종료 시간 계산, 실행시간 측정
		printf("%6d    %f\n", n, duration);
		if (n == 100) {
			step = 100;
		}
	}
}
void sort(int list[], int n) {  //소트함수 정의
	int i, j, min, temp;
	//선택 정렬
	for (i = 0; i < n - 1; i++) {
		min = i; //최소값 초기화
		for (j = i + 1; j < n; j++) { //현재요소 이후의 모든값에 대해서
			if (list[j] < list[min]) { //최소값 찾기
				min = j; //최소값 갱신
			}
		}
		SWAP(list[i], list[min], temp);
	}
}
