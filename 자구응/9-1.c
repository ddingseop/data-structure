//2020111842 금명섭
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
} element;

void listAddq(element key, element* que, int size);
void cirAddq(element key, element* que, int size);
void listDeleteq(element* que);
void cirDeleteq(element* que, int size);
void queueFull();
void queueEmpty();

int listfront = -1;
int listrear = -1;
int cirfront = 0;
int cirrear = 0;

int main(void)
{
    FILE* fp = fopen("in1.txt", "r");
    int size;
    fscanf(fp, "%d", &size);
    element* cirQue = malloc(sizeof(element) * size);
    element* listQue = malloc(sizeof(element) * size);
    printf("Queue size : %d\n", size);
    char n;
    element val;
    while (fscanf(fp, "%c", &n) != EOF)
    {
        if (n == 'a')
        {
            fscanf(fp, "%d", &val);
            printf("\nadd %d...\n", val);
            printf("[Circular queue] ");
            cirAddq(val, cirQue, size);
            printf("\n");
            printf("[List queue] ");
            listAddq(val, listQue, size);
        }
        else if (n == 'd')
        {
            printf("\nDelete\n");
            printf("[Circular queue] ");
            cirDeleteq(cirQue, size);
            printf("\n");
            printf("[List queue] ");
            listDeleteq(listQue, size);
        }
    }

}

void listAddq(element key, element* que, int size)
{
    if (listrear == size - 1)
    {
        queueFull();
        return;
    }
    else
    {
        que[++listrear] = key;
        for (int i = listfront + 1; i <= listrear; i++)
            printf("%d ", que[i]);
    }
}
void cirAddq(element key, element* que, int size)
{
    cirrear = (cirrear + 1) % size;
    if (cirfront == cirrear) {
        queueFull();
        cirrear -= 1;
        return;
    }

    que[cirrear] = key;
    for (int i = (cirfront + 1) % size; i != (cirrear + 1) % size; i = (i + 1) % size) {
        printf("%d ", que[i]);
    }
}
void listDeleteq(element* que)
{
    if (listfront == listrear) {  //전 상황이 이미 비어있는 경우
        queueEmpty();
    }
    ++listfront;
    if (listfront == listrear) {  //front + 해준뒤 빈 경우
        queueEmpty();
    }
    else {

        for (int i = listfront + 1; i <= listrear; i++)
            printf("%d ", que[i]);
    }
}
void cirDeleteq(element* que, int size) {
    if (cirfront == cirrear) {   //전 상황이 이미 비어있는 경우
        queueEmpty();
        return;
    }
    cirfront = (cirfront + 1) % size;
    if (cirfront == cirrear) {   //front + 해준뒤 빈 경우
        queueEmpty();
    }
    else {
        if (cirrear <= 0) {
            cirrear += size;
        }
        for (int i = (cirfront + 1) % size; i != (cirrear + 1) % size; i = (i + 1) % size) {
            //cirfront 다음 위치부터 시작하여 cirrear 다음 위치에 도달하기 전까지 반복,
            //i를 다음위치로 이동시킴 다 %size를 함으로써 배열의 범위를 나가지않고 순환구조 유지
            printf("%d ", que[i]);
        }
    }
}
void queueFull() {
    printf("Full.");
}
void queueEmpty() {
    printf("Empty.");
}