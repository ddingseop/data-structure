//2020111842 �ݸ�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
int indegree[MAX] = { 0 };
int outdegree[MAX] = { 0 };

typedef struct ListNode {
    int vertex;
    struct ListNode* next;
} ListNode;

typedef struct Graph {
    int nVertex;
    ListNode** adjLists; // ��ũ�� ����Ʈ�� �迭
} Graph;

Graph* createGraph(int n) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->nVertex = n;
    graph->adjLists = (ListNode**)malloc(n * sizeof(ListNode*));
    for (int i = 0; i < n; ++i) {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int from, int to) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->vertex = to;
    newNode->next = graph->adjLists[from];
    //graph->adjLists[from]�� from������ ����� ����Ʈ ù��° ����ε� �� ��尡 ������ ���� ����Ʈ�� ù ��° ��带 ����Ű�� ��
    graph->adjLists[from] = newNode;//graph->adjLists[from]�� newNode�� �ʱ�ȭ����
}  //����� �� ��带 graph->adjLists[from] �տ� �ְ� �� ��带 graph->adjLists[from]�� �ʱ�ȭ

void printMatrix(Graph* graph) {
    printf("Adjacency matrix\n");
    for (int i = 0; i < graph->nVertex; ++i) {
        for (int j = 0; j < graph->nVertex; ++j) {
            int isAdjacent = 0;
            ListNode* temp = graph->adjLists[i];
            while (temp) {
                if (temp->vertex == j) {
                    isAdjacent = 1;
                    break;
                }
                temp = temp->next;
            }
            printf("%2d ", isAdjacent);
        }
        printf("\n");
    }
    printf("\n");
}

void printList(Graph* graph) {
    for (int i = 0; i < graph->nVertex; ++i) {
        ListNode* temp = graph->adjLists[i];
        printf("[ %d]", i);
        while (temp) { //�� ������ ��������Ʈ�� ��ȸ�ϸ� ����� ���� ���
            printf("  %d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
    printf("\n");
}


void printDegree(Graph* graph) {
    printf("Indegree\n");
    for (int i = 0; i < graph->nVertex; ++i) {
        printf("[%2d] %d\n", i, indegree[i]);
    }
    printf("\n");
    printf("Outdegree\n");
    for (int i = 0; i < graph->nVertex; ++i) {
        printf("[%2d] %d\n", i, outdegree[i]);
    }

}

int main() {
    FILE* fp;
    fp = fopen("in.txt", "r");

    int n1;
    fscanf(fp, "%d", &n1);

    Graph* graph = createGraph(n1);
    Graph* inverse_graph = createGraph(n1);

    int from, to;
    while (fscanf(fp, "%d %d", &from, &to) != EOF) {
        addEdge(graph, from, to);
        addEdge(inverse_graph, to, from);
        outdegree[from]++;
        indegree[to]++;
    }
    fclose(fp);

    printMatrix(graph);
    printf("Linked adjacency list\n");
    printList(graph);
    printf("Inverse adjacency list\n");
    printList(inverse_graph);
    printDegree(graph);

    return 0;
}
