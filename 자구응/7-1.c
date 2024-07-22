//2020111842 금명섭
#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int row;
    int col;
    int dir;
} element;

typedef struct {
    int vert;
    int horiz;
} offsets;

offsets move[4] = { {-1,0},{0,1},{1,0},{0,-1} };

int top = -1;
void push(element item, element* stack);
element pop(element* stack);
void stackFull();
element stackEmpty();

void initializeArray(int** arr, int row, int col);
void initializeMark(int** mark, int row, int col);
int** readMaze(FILE* fp, int* row, int* col, int* startrow, int* startcol, int* finishrow, int* finishcol);
void freeArray(int** arr, int row);
void freeMark(int** mark, int row);
void path(int** maze, int** mark, offsets* move, int startrow, int startcol, int finishrow, int finishcol, int mazerow, int mazecol);
int same(element* stack, int row, int col, int top);

int main(void)
{
    FILE* files[4];
    files[0] = fopen("maze1.txt", "r");
    files[1] = fopen("maze2.txt", "r");
    files[2] = fopen("maze3.txt", "r");
    files[3] = fopen("maze4.txt", "r");

    for (int i = 0; i< 4; i++) {
        int row, col, startrow, startcol, finishrow, finishcol;
        int** maze = readMaze(files[i], &row, &col, &startrow, &startcol, &finishrow, &finishcol);
        if (maze == NULL) {
            printf("Failed to read maze %d\n", i + 1);
            continue;
        }

        printf("MAZE%d\n", i + 1);
        for (int i = 1; i <= row ; i++) {
            for (int j = 1; j <= col; j++)
                printf("%d ", maze[i][j]);
            printf("\n");
        }
        int** mark = (int**)malloc(sizeof(int*) * (row + 2));
        initializeMark(mark, row, col);

        path(maze, mark, move, startrow + 1, startcol + 1, finishrow + 1, finishcol + 1, row, col);

        freeArray(maze, row);
        freeMark(mark, row);
        fclose(files[i]);
    }

    return 0;
}

void initializeArray(int** arr, int row, int col) { //배열 동적할당함수
    for (int i = 0; i < row + 2; i++) {
        arr[i] = (int*)malloc(sizeof(int) * (col + 2));
        for (int j = 0; j < col + 2; j++) {
            if (i == 0 || j == 0 || i == row + 1 || j == col + 1)
                arr[i][j] = 1;
            else
                arr[i][j] = 0;
        }
    }
}
void initializeMark(int** mark, int row, int col) { //방문배열 동적할당함수
    for (int i = 0; i < row + 2; i++) {
        mark[i] = (int*)malloc(sizeof(int) * (col + 2));
        for (int j = 0; j < col + 2; j++)
            mark[i][j] = 0;
    }
}
//파일에서 배열 읽어오기
int** readMaze(FILE* fp, int* row, int* col, int* startrow, int* startcol, int* finishrow, int* finishcol) {
    if (fp == NULL)
        return NULL;

    fscanf(fp, "%d %d", row, col);
    int** maze = (int**)malloc(sizeof(int*) * (*row + 2));
    initializeArray(maze, *row, *col);

    for (int i = 1; i <= *row; i++) {
        for (int j = 1; j <= *col; j++)
            fscanf(fp, "%d", &maze[i][j]);
    }

    fscanf(fp, "%d %d", startrow, startcol);
    fscanf(fp, "%d %d", finishrow, finishcol);

    return maze;
}

void freeArray(int** arr, int row) {
    for (int i = 0; i < row + 2; i++)
        free(arr[i]);
    free(arr);
}

void freeMark(int** mark, int row) {
    for (int i = 0; i < row + 2; i++)
        free(mark[i]);
    free(mark);
}

void push(element item, element* stack)
{
    if (top >= MAX_STACK_SIZE - 1)
        stackFull();
    stack[++top] = item;
}

element pop(element* stack)
{
    if (top == -1)
        return stackEmpty();
    return stack[top--];
}

void stackFull()
{
    fprintf(stderr, "Stack is full");
    exit(EXIT_FAILURE);
}

element stackEmpty()
{
    fprintf(stderr, "Stack is empty");
    exit(EXIT_FAILURE);
}

void path(int** maze, int** mark, offsets* move, int startrow, int startcol, int finishrow, int finishcol, int mazerow, int mazecol)
{
	int i, row, col, nextrow, nextcol, dir, found = false;
	element position; //현재위치 정보 저장
	element stack[MAX_STACK_SIZE]; //스택선언
	top = -1; //스택 비어있음
	mark[startrow][startcol] = 1; //시작점 방문표시
	top = 0; //스택에 시작점이 하나 저장됨
	stack[0].row = startrow; stack[0].col = startcol; stack[0].dir = 0;

	while (top > -1 && !found) //스택이 비어있지 않고 도착하지 않을동안
	{
		position = pop(stack); //스택에서 위치정보 가져옴
		row = position.row; //row변수에 위치정보 저장
		col = position.col; //col변수에 위치정보 저장
		dir = position.dir; //dir변수에 위치정보 저장

		while (dir < 4 && !found) //모든방향에 대해 반복
		{
			nextrow = row + move[dir].vert; //다음위치 계산(이동방향에 따라 조절)
			nextcol = col + move[dir].horiz; //다음위치 계산(이동방향에 따라 조절)
			if (nextrow == finishrow && nextcol == finishcol) //다음위치가 도착점이라면
				found = true; //반복종료
			else if (!maze[nextrow][nextcol] && !mark[nextrow][nextcol]) //0이라면 이동할수 있는거니까
			{
				mark[nextrow][nextcol] = 1; //방문표시
				position.row = row; //현재위치정보 저장
				position.col = col; //현재위치정보 저장
				position.dir = ++dir; //다음방향으로 탐색하기위해 방향 증가
				push(position, stack); //해당위치 스택에 추가
				row = nextrow; //다음위치로 이동
				col = nextcol; //다음위치로 이동
				dir = 0; //방향 초기화해줌
			}
			else ++dir; //다음 위치로 갈수 없다면 이동방향 변경
		}
	}
	if (found)
	{
		printf("The path is : \n");
		for (int i = 1; i <= mazerow; i++)
		{
			for (int j = 1; j <= mazecol; j++)
			{
				if (i == startrow && j == startcol)
					printf("S ");
				else if (i == finishrow && j == finishcol)
					printf("F ");
				else if (same(stack, i, j, top) == 1)
					printf("X ");
				else if (row == i && col == j)
					printf("X ");
				else
					printf("%d ", maze[i][j]);

			}
			printf("\n");
		}

	}
	else {
		printf("No path!\n");
		for (int i = 1; i <= mazerow; i++)
		{
			for (int j = 1; j <= mazecol; j++)
			{
				if (i == startrow && j == startcol)
					printf("S ");
				else if (i == finishrow && j == finishcol)
					printf("F ");
				else if (same(stack, i, j, top) == 1)
					printf("X ");
				else
					printf("%d ", maze[i][j]);

			}
			printf("\n");
		}
	}

}

int same(element* stack, int row, int col, int top)
{
	int num = 0;
	for (int i = 0; i <= top; i++) {
		if (stack[i].row == row && stack[i].col == col)
			num = 1;
	}
	return num;
}

