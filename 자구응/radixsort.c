//2020111842 �ݸ�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct {
    int grade;
    char class;
    int number;
} element;

element id_Int(char* id_Str) { //����ȭ�ϱ�
    element id;
    if (strlen(id_Str) == 4) { 
        id.grade = id_Str[0] - '0';
        id.class = id_Str[1];
        id.number = (id_Str[2] - '0') * 10 + (id_Str[3] - '0');
    }
    return id;
}

int digit(element id, int d) {
    if (d == 0) return id.number - 1; // ��ȣ (0-19)
    if (d == 1) return id.class - 'A'; // �� (0-5)
    return id.grade - 1; // �г� (0-2)
}

int radixSort(element a[], int link[], int n) {
    int front[20], rear[20]; 
    int bin, current, first, last;

    first = 1;
    for (int i = 1; i < n; i++) { //�ʹ� ��ũ�迭 ����
        link[i] = i + 1;
    }
    link[n] = 0;

    
    for (int i = 0; i < 3; i++) { //0�϶� ��ȣ, 1�϶� ��, 2�϶� �г�
        int radix = (i == 0 ? 20 : (i == 1 ? 6 : 3)); //i�� ���� radixũ�� ����
        
        for (bin = 0; bin < radix; bin++) { //front �ʱⰪ �ֱ�
            front[bin] = 0;
        }

        for (current = first; current; current = link[current]) {
            bin = digit(a[current], i);
            if (front[bin] == 0) {  //����Ʈ ���������
                front[bin] = current; //�߰�
            }
            else { //�ȿ� ������ 
                link[rear[bin]] = current; //link�迭 �̾��ְ�
            }
            rear[bin] = current; //rear �ٲ��ֱ�
        }
        //�� �ڸ����� ���� ù��°�� ��Ÿ���� ��, ���������� ��Ÿ���� ���� ã��
        for (bin = 0; bin < radix && !front[bin]; bin++);
        first = front[bin];
        last = rear[bin];
        //�� �ڸ����� ���� ��ũ�迭 ������
        for (bin++; bin < radix; bin++) {
            if (front[bin]) {
                link[last] = front[bin];
                last = rear[bin];
            }
        }
        link[last] = 0;
    }
    return first;
}

int main() {
    FILE* fp = fopen("in.txt", "r");
    int n;
    fscanf(fp, "%d", &n);

    element ids[MAX];
    int link[MAX];
    char buffer[5];

    for (int i = 1; i <= n; i++) {
        fscanf(fp, "%s", buffer);
        ids[i] = id_Int(buffer);
    }
    fclose(fp);

    int sorted = radixSort(ids, link, n);

    printf("[");
    for (int i = sorted; i; i = link[i]) {
        printf("%d%c%02d", ids[i].grade, ids[i].class, ids[i].number);
        if (link[i]) printf("] [");
    }
    printf("]\n");

    return 0;
}
