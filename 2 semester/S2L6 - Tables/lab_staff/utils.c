//
// Created by den41 on 25.05.2024.
//
#include <stdio.h>
#include "../table_shit/table.h"

void linear_selection_sort(Table* table) {
    for (long long i = 0; i < table->count - 1; i++) {
        long long min_index = i;
        for (long long j = i + 1; j < table->count; j++) {
            if (table->keys[j].int_part < table->keys[min_index].int_part ||
                (table->keys[j].int_part == table->keys[min_index].int_part &&
                 table->keys[j].char_part < table->keys[min_index].char_part)) {
                min_index = j;
            }
        }
        if (min_index != i) {
            Key temp_key = table->keys[i];
            void* temp_value = table->values[i];
            table->keys[i] = table->keys[min_index];
            table->values[i] = table->values[min_index];
            table->keys[min_index] = temp_key;
            table->values[min_index] = temp_value;
        }
    }
}

void* get_value(Table* table, long long key_int, char key_char) {
    for (int i = 0; i < table->count; i++) {
        if (table->keys[i].int_part == key_int && table->keys[i].char_part == key_char) {
            return table->values[i];
        }
    }
    return NULL; // Key not found
}

void* binary_search(Table* table, long long key_int, char key_char) {
    long long left = 0;
    long long right = table->count;

    while (left <= right) {
        long long mid = (left + right) / 2;

        if (table->keys[mid].int_part == key_int && table->keys[mid].char_part == key_char) {
            return table->values[mid]; // Key found, return the index
        }
        else if (table->keys[mid].int_part < key_int ||
                 (table->keys[mid].int_part == key_int && table->keys[mid].char_part < key_char)) {
            left = mid; // Search in the right subarray
        }
        else {
            right = mid; // Search in the left subarray
        }
    }

    return NULL; // Key not found
}

void display_table(Table* table) {
    printf("Current Table:\n");
    for (int i = 0; i < table->count; i++) {
        printf("Key: %lld%c, Value: %s\n", table->keys[i].int_part, table->keys[i].char_part, (char*)table->values[i]);
    }
    printf("\n");
}