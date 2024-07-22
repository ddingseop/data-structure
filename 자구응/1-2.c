//2020111842 금명섭
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct { //구조체 정의
    char name[50];
    int score;
    int age;
} Student;

int main() {
    FILE* fp;
    int num_students;

    // 파일 열기
    fp = fopen("in.txt", "r");
    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    // 학생 수 읽기
    fscanf(fp, "%d", &num_students);

    // 학생 데이터 배열 동적 할당
    Student* students = (Student*)malloc(num_students * sizeof(Student));

    // 학생 데이터 읽기
    for (int i = 0; i < num_students; i++) {
        fscanf(fp, "%s %d %d", students[i].name, &students[i].score, &students[i].age);
    }

    // 특정 점수 이상을 받은 학생들의 이름 출력
    int cutoff_score;
    printf("기준점수 입력: ");
    scanf("%d", &cutoff_score);

    printf("%d점 이상인 학생들 명단:\n", cutoff_score);
    for (int i = 0; i < num_students; i++) {
        if (students[i].score >= cutoff_score) {
            printf("이름: %s, 성적: %d, 나이: %d\n", students[i].name, students[i].score, students[i].age);
        }
    }

    // 메모리 해제 및 파일 닫기
    free(students);
    fclose(fp);

    return 0;
}
