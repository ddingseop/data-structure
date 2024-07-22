//2020111842 금명섭
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 10

int graph[MAX][MAX];
int visited[MAX];
int n;

void read_graph(const char* fname) {
    FILE* fp = fopen(fname, "r");
    fscanf(fp, "%d", &n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fscanf(fp, "%d", &graph[i][j]);
        }
    }
    fclose(fp);
}

void dfs(int v) {
    printf("%3d ", v);
    visited[v] = 1;
    for (int i = 0; i < n; ++i) {
        if (graph[v][i] && !visited[i]) {
            dfs(i);
        }
    }
}

void bfs(int start) {
    int queue[MAX], front = 0, rear = 0;
    visited[start] = 1;
    queue[rear++] = start; //큐에 start 노드 추가(addq)
    printf("%3d ", start);
    while (front < rear) {
        int v = queue[front++]; //큐에서 노드 v 꺼내기(deleteq)
        for (int i = 0; i < n; ++i) {
            if (graph[v][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i; //i를 큐에 추가(addq)
                printf("%3d ", i);
            }
        }
    }
}

void dfs_component(int start) {
    printf("Component %d: ", start);
    dfs(start);
    printf("\n");
}

void bfs_component(int start) {
    printf("Component %d: ", start);
    bfs(start);
    printf("\n");
}

void dfs_spanning_tree(int v, int parent) {
    visited[v] = 1;
    for (int i = 0; i < n; ++i) {
        if (graph[v][i] && !visited[i]) {
            printf("(%d, %d) ", v, i);
            dfs_spanning_tree(i, v);
        }
    }
}

void bfs_spanning_tree(int start) {
    int queue[MAX], front = 0, rear = 0;
    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int v = queue[front++];
        for (int i = 0; i < n; ++i) {
            if (graph[v][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
                printf("(%d, %d) ", v, i);
            }
        }
    }
}

void revisited() {
    for (int i = 0; i < n; ++i) {
        visited[i] = 0;
    }
}

int main() {
    read_graph("in.txt");
    int start;

    printf("[DFS]\n");
    while (1) {
        printf("Input starting number:");
        scanf("%d", &start);
        if (start == -1) {
            break;
        }
        revisited();
        dfs(start);
        printf("\n");
    }
    printf("[BFS]\n");
    while (1) {
        printf("Input starting number:");
        scanf("%d", &start);
        if (start == -1) {
            break;
        }
        revisited();
        bfs(start);
        printf("\n");
    }
    printf("\n[DFS Component]\n");
    revisited();
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs_component(i);
        }
    }
    printf("[BFS Component]\n");
    revisited();
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            bfs_component(i);
        }
    }
    printf("\n[DFS Spanning Tree]\n");
    while (1) {
        printf("Input starting number: ");
        scanf("%d", &start);
        if (start == -1) {
            break;
        }
        revisited();
        dfs_spanning_tree(start, -1);
        printf("\n");
    }
    printf("[BFS Spanning Tree]\n");
    while (1) {
        printf("Input starting number: ");
        scanf("%d", &start);
        if (start == -1) {
            break;
        }
        revisited();
        bfs_spanning_tree(start);
        printf("\n");
    }
    return 0;
}