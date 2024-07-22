#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STUDENTS 9

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void addEdge(struct Node* adjList[], int u, int v) {
    struct Node* newNode = createNode(v);
    newNode->next = adjList[u];
    adjList[u] = newNode;

    newNode = createNode(u);
    newNode->next = adjList[v];
    adjList[v] = newNode;
}

void deleteEdge(struct Node* adjList[], int u, int v) {
    struct Node* temp = adjList[u];
    struct Node* prev = NULL;
    while (temp != NULL && temp->data != v) {
        prev = temp;
        temp = temp->next;
    }
    if (temp != NULL) {
        if (prev != NULL) {
            prev->next = temp->next;
        }
        else {
            adjList[u] = temp->next;
        }
        free(temp);
    }
    temp = adjList[v];
    prev = NULL;
    while (temp != NULL && temp->data != u) {
        prev = temp;
        temp = temp->next;
    }
    if (temp != NULL) {
        if (prev != NULL) {
            prev->next = temp->next;
        }
        else {
            adjList[v] = temp->next;
        }
        free(temp);
    }
}

void findMaxFriends(struct Node* adjList[]) {
    int maxFriends = 0;
    int student = -1;
    for (int i = 0; i < MAX_STUDENTS; i++) {
        int count = 0;
        struct Node* temp = adjList[i];
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
        if (count > maxFriends) {
            maxFriends = count;
            student = i;
        }
    }
    printf("가장 친구가 많은 학생의 번호: [%d]: %d명\n", student, maxFriends);
}

void dfs(int v, int visited[], struct Node* adjList[], int component[], int* size) {
    visited[v] = 1;
    component[*size] = v;
    (*size)++;
    struct Node* temp = adjList[v];
    while (temp != NULL) {
        if (!visited[temp->data]) {
            dfs(temp->data, visited, adjList, component, size);
        }
        temp = temp->next;
    }
}

void printConnectedComponents(struct Node* adjList[]) {
    int visited[MAX_STUDENTS] = { 0 };
    int component[MAX_STUDENTS];

    printf("Connected component after deleting\n");
    for (int v = 0; v < MAX_STUDENTS; v++) {
        if (!visited[v]) {
            int size = 0;
            dfs(v, visited, adjList, component, &size);
            if (size > 0) {
                printf("Connected component: ");
                for (int i = 0; i < size; i++) {
                    printf("%d ", component[i]);
                }
                printf("\n");
            }
        }
    }
}

int main() {
    struct Node* adjList[MAX_STUDENTS] = { NULL };
    FILE* file = fopen("in3.txt", "r");

    int edgeCount;
    fscanf(file, "%d", &edgeCount);

    for (int i = 0; i < edgeCount; i++) {
        int u, v;
        fscanf(file, "%1d%1d", &u, &v);
        addEdge(adjList, u, v);
    }
    fclose(file);

    findMaxFriends(adjList);

    int u, v;
    while (1) {
        printf("Input deleting node(x, y): ");
        scanf("%d, %d", &u, &v);
        if (u == -1 && v == -1) {
            break;
        }
        deleteEdge(adjList, u, v);
    }

    printConnectedComponents(adjList);

    for (int i = 0; i < MAX_STUDENTS; i++) {
        struct Node* temp = adjList[i];
        while (temp != NULL) {
            struct Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    return 0;
}
