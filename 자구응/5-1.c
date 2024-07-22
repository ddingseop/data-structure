//2020111842 금명섭
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct { //구조체 정의
	int coef;  //계수
	int expon; //지수
} polynomial;

int avail = 0;
polynomial* terms;

int compare(int A, int B) { //비교함수
    if (A > B)
        return 1;
    else if (A == B)
        return 0;
    else
        return -1;
}

void attach(int coefficient, int exponent) { 
    terms[avail].coef = coefficient;
    terms[avail++].expon = exponent;
}

void padd(int sa, int fa, int sb, int fb, int* sd, int* fd) {
    int coef;
    *sd = avail; //C식 위치
    while (sa <= fa && sb <= fb)
        switch (compare(terms[sa].expon, terms[sb].expon)) {
        case 1:
            attach(terms[sb].coef, terms[sb].expon);
            sb++;
            break;
        case 0:
            coef = terms[sa].coef + terms[sb].coef;
            if (coef)
                attach(coef, terms[sa].expon);
            sb++;
            sa++;
            break;
        case -1:
            attach(terms[sa].coef, terms[sa].expon);
            sa++;
        }
    for (; sa <= fa; sa++) //A항이 남아있으면
        attach(terms[sa].coef, terms[sa].expon);
    for (; sb <= fb; sb++)  //B항이 남아있으면
        attach(terms[sb].coef, terms[sb].expon);
    *fd = avail - 1;  //연산끝나면 avail이 빈칸을 가르켜서 끝을 avail-1로 설정
}

int main() {
    FILE* iF, * oF;
    int sA, fA, sB, fB, sC, fC;
    int numA, numB, numC;  //항의 개수

    iF = fopen("in1.txt", "r");
    fscanf(iF, "%d %d", &numA, &numB);

    terms = (polynomial*)malloc((numA + numB + 1) * 2 *  sizeof(polynomial)); //동적할당
    avail = numA + numB; // terms에서 A식 B식 채워지고 numA+numB번째부터 C식 채워짐
    for (int i = 0; i < numA; i++) {
        fscanf(iF, "%d", &terms[i].coef);
        fscanf(iF, "%d", &terms[i].expon);
    }
    fA = numA - 1;

    for (int i = 0; i < numB; i++) {
        fscanf(iF, "%d", &terms[numA + i].coef);
        fscanf(iF, "%d", &terms[numA + i].expon);
    }
    fB = numA + numB - 1;
    fclose(iF);

    oF = fopen("out1.txt", "w");
    padd(0, fA, numA, fB, &sC, &fC);
    numC = fC - sC + 1;

    if (fC - sC + 1 != 0) {  
        fprintf(oF, "%d ", numC);
        for (int i = sC; i <= fC; i++) {
            fprintf(oF, "%d %d ", terms[i].coef, terms[i].expon);
        }
    }
    else {  //항의 개수 0개 일때(두 함수 합이 0일때)
        fprintf(oF, "%d ", fC - sC + 1);
        fprintf(oF, "%d", 0);
    }
    fclose(oF);
    free(terms);

    return 0;
}

//padd함수에서  *sd = avail; 이 부분이 있는데  avail = numA + numB;를 해줘야 함수 시작을 저기서 시작함