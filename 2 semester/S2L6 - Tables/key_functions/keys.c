//
// Created by den41 on 25.05.2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "../table_shit/table.h"


void ordered_assignment(Table* table) {
    char input[100];
    long long count = 0;
    int delta = 0;
    FILE* file = fopen("../song.txt", "r");
    if (file == NULL) {
        printf("Error opening file 'song.txt'.\n");
        return;
    }

    while (fgets(input, sizeof(input), file) != NULL) {
        input[strcspn(input, "\n")] = '\0'; // Remove newline character
        if (strlen(input) > 0) {
            char* value = (char*)malloc(strlen(input) + 1);
            strcpy(value, input);
            add_entry(table, count, 'a' + delta, value);
            delta++;
            if (delta == 25) {
                count++;
                delta = 0;
            }
        }
    }

    fclose(file);
}

void reverse_ordered_assignment(Table* table) {
    char input[100];
    long long count = LONG_LONG_MAX;
    int delta = 25;
    FILE* file = fopen("../song.txt", "r");
    if (file == NULL) {
        printf("Error opening file 'song.txt'.\n");
        return;
    }

    while (fgets(input, sizeof(input), file) != NULL) {
        input[strcspn(input, "\n")] = '\0'; // Remove newline character
        if (strlen(input) > 0) {
            char* value = (char*)malloc(strlen(input) + 1);
            strcpy(value, input);
            add_entry(table, count, 'a' + delta, value);
            delta--;
            if (delta == -1) {
                count--;
                delta = 25;
            }
        }
    }
}

void random_assignment(Table* table) {
    char input[100];
    FILE* file = fopen("../song.txt", "r");
    if (file == NULL) {
        printf("Error opening file 'song.txt'.\n");
        return;
    }
    srand(time(NULL)); // Seed the random number generator
    while (fgets(input, sizeof(input), file) != NULL) {
        input[strcspn(input, "\n")] = '\0'; // Remove newline character
        if (strlen(input) > 0) {
            char* value = (char*)malloc(strlen(input) + 1);
            strcpy(value, input);
            long long key_int = rand();
            char key_char = 'a' + (rand() % 26);
            add_entry(table, key_int, key_char, value);
        }
    }
}
