//2020111842 �ݸ�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int u, v, weight;
} Edge;

int parent[MAX]; //�� ������ �θ� ����
Edge edges[MAX]; //��� ���� ����
Edge result[MAX]; //mst ���� ����
int edge_count = 0; //������ ��
int n; //�׷��� ���� ��

//�־��� ���� i�� ��Ʈã��
int find(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

// i,j������ ���� �������� ��ġ��
void union_sets(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    parent[root_i] = root_j;
}

void readFile(const char* filename) {
    FILE* fp = fopen(filename, "r");
    fscanf(fp, "%d", &n);
    int cost;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fscanf(fp, "%d", &cost);
            if (cost != 0 && i < j) {
                edges[edge_count].u = i;
                edges[edge_count].v = j;
                edges[edge_count].weight = cost;
                edge_count++;
            }
        }
    }
    fclose(fp);
}

int compare(const void* a, const void* b) {
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    return edgeA->weight - edgeB->weight;
}

void kruskal() {
    // qsort�� ����ġ �������� �����ϱ�
    qsort(edges, edge_count, sizeof(Edge), compare);

    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    int result_count = 0;

    for (int i = 0; i < edge_count; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int weight = edges[i].weight;

        // ����Ŭ�� �ƴϸ� ���Խ�Ŵ
        if (find(u) != find(v)) {
            result[result_count++] = edges[i];
            union_sets(u, v);
        }
    }

    printf("(edge):weight\n");
    for (int i = 0; i < result_count; i++) {
        printf("(%d, %d): %d\n", result[i].u, result[i].v, result[i].weight);
    }
}

int main() {
    readFile("in.txt");
    kruskal();
    return 0;
}
