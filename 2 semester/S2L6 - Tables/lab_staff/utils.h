//
// Created by den41 on 25.05.2024.
//

#ifndef PRACTICE9_UTILS_H
#define PRACTICE9_UTILS_H
#include "../table_shit/table.h"

void linear_selection_sort(Table* table);
void* get_value(Table* table, long long key_int, char key_char);
void* binary_search(Table* table, long long key_int, char key_char);
void display_table(Table* table);
#endif //PRACTICE9_UTILS_H
