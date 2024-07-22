//2020111842 금명섭
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 이진 표현 출력 함수
void printBinary(int n) {
    if (n > 1)
        printBinary(n / 2); //2로 나누면서
    printf("%d", n % 2); //재귀로 이진수 구하기
}

// '0'의 개수 계산 함수
int countZeros(int n) {
    if (n == 0)
        return 1; // 0인 경우 '0'의 개수는 1
    else if (n == 1)
        return 0; // 1인 경우 '0'의 개수는 0
    else if (n % 2 == 0)
        return countZeros(n / 2) + 1; // 짝수인 경우, [N/2]의 '0' 개수 + 1
    else
        return countZeros(n / 2); // 홀수인 경우, [N/2]의 '0' 개수
}

int main() {
    int N;
    do {
        printf("Input num: ");
        scanf_s("%d", &N);
        if (N < 0) {
            printf("Exit");  //예외처리
            return 0;
        }
        printf("2진표현: ");
        printBinary(N);

        printf("\n%d내 0은 %d개 있다.\n", N, countZeros(N));
    } while (1);

    return 0;
}