//2020111842 금명섭
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b;
    //파일 읽어오기
    FILE* fp1 = fopen("in1.txt", "r");
    FILE* fp2 = fopen("in2.txt", "r");

    if (!fp1 || !fp2) {
        printf("no");
        exit(1);
    }
    //값 읽어오기
    fscanf(fp1, "%d", &a);
    fscanf(fp2, "%d", &b);

    while (!feof(fp1) && !feof(fp2)) {
        if (a > b) { //첫번째 파일값이 더 큰경우
            fscanf(fp1, "%d", &a); //첫번째 파일 다음값 불러옴
            continue;
        }
        else if (a < b) { //두번째 파일값이 더 큰경우
            fscanf(fp2, "%d", &b); //두번째 파일 다음값 불러옴
            continue;
        }
        else { //두 파일값이 같은경우
            printf("%d ", a);  //출력하고
            fscanf(fp1, "%d", &a); //첫번째 파일 다음값 불러옴
            fscanf(fp2, "%d", &b); //두번째 파일도 다음값 불러옴
            continue;
        }
    }
    fclose(fp1);
    fclose(fp2);
}