//2020111842 금명섭
#include <stdio.h>
// #define _CRT_SECURE_NO_WARNINGS

int main() {
    // FILE* fp = fopen("out.txt", "w"); //파일 쓰기모드로 열기
    FILE* fp;
    fopen_s(&fp, "out.txt", "w");


    int count = 0;
    int sum = 0;
    int min = 100; // 초기 최소값을 100으로 설정
    int max = 1;   // 초기 최대값을 1로 설정

    int num;
    printf("Input number:\n");
    // while (fscanf(stdin, "%d", &num) != EOF)
    while (fscanf_s(stdin, "%d", &num) != EOF) { //입력종료할때까지 받기
        if (num < 1 || num > 100) {  //범위 제한
            continue;
        }
        count++; //입력받는 개수 더해주기
        sum += num; //입력받는 수의 합 구하기
        if (num < min) {
            min = num; //최소값
        }
        if (num > max) {
            max = num; //최대값
        }
    }
    if (count > 0) {
        int average = (int)sum / count;
        fprintf(fp, "MIN: %d MAX: %d, AVG: %d\n", min, max, average);
    }
    fclose(fp); //파일닫기
    return 0;
}