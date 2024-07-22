//2020111842 ±Ý¸í¼·
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SLOT_SIZE 3
#define MAX 100

typedef struct {
    char keys[SLOT_SIZE][MAX];
    int count;
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
    for (int i = 0; i < bucket_size; i++) {
        int try = (index + i) % bucket_size;
        if (table[try].count < SLOT_SIZE) {
            strcpy(table[try].keys[table[try].count++], key);
            return;
        }
    }
}

int search(Bucket* table, int bucket_size, const char* key) {
    int index = hash_function(key, bucket_size);
    for (int i = 0; i < bucket_size; i++) {
        int try = (index + i) % bucket_size;
        for (int j = 0; j < table[try].count; j++) {
            if (strcmp(table[try].keys[j], key) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void print_table(Bucket* table, int bucket_size) {
    for (int i = 0; i < bucket_size; i++) {
        printf("[%2d]:", i);
        for (int j = 0; j < table[i].count; j++) {
            printf("%12s", table[i].keys[j]);
        }
        printf("\n");
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
    printf("Input bucket size: ");
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
    free(table);
    return 0;
}