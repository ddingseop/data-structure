//2020111842 ±Ý¸í¼·
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct Node {
    char key[MAX];
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} Bucket;

int hash_function(const char* key, int bucket_size) {
    int sum = 0;
    while (*key) {
        sum += (unsigned char)*key++;
    }
    return sum % bucket_size;
}

void insert(Bucket* table, int bucket_size, const char* key) {
    int index = hash_function(key, bucket_size);
    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->key, key);
    new_node->next = table[index].head;
    table[index].head = new_node;
}

int search(Bucket* table, int bucket_size, const char* key) {
    int index = hash_function(key, bucket_size);
    Node* current = table[index].head;
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void print_table(Bucket* table, int bucket_size) {
    for (int i = 0; i < bucket_size; i++) {
        printf("[%2d]:", i);
        Node* current = table[i].head;
        while (current) {
            printf(" [%s]", current->key);
            current = current->next;
        }
        printf("\n");
    }
}

void free_table(Bucket* table, int bucket_size) {
    for (int i = 0; i < bucket_size; i++) {
        Node* current = table[i].head;
        while (current) {
            Node* to_free = current;
            current = current->next;
            free(to_free);
        }
    }
}

int main() {
    FILE* fp = fopen("in.txt", "r");

    int num_keys;
    fscanf(fp, "%d", &num_keys);

    char(*keys)[MAX] = malloc(num_keys * MAX * sizeof(char));


    for (int i = 0; i < num_keys; i++) {
        fscanf(fp, "%s", keys[i]);
    }
    fclose(fp);

    int bucket_size;
    printf("Input size: ");
    scanf("%d", &bucket_size);

    Bucket* table = (Bucket*)calloc(bucket_size, sizeof(Bucket));

    for (int i = 0; i < num_keys; i++) {
        insert(table, bucket_size, keys[i]);
    }

    print_table(table, bucket_size);

    char query[MAX];
    printf("\n");
    while (1) {
        printf("Input string(Q for quit): ");
        scanf("%s", query);
        if (strcmp(query, "Q") == 0) {
            printf("Exit\n");
            break;
        }
        if (search(table, bucket_size, query)) {
            printf("Success\n");
        }
        else {
            printf("Fail\n");
        }
    }

    free(keys);
    free_table(table, bucket_size);
    free(table);
    return 0;
}