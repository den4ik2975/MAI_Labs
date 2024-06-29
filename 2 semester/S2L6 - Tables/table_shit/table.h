//
// Created by den41 on 25.05.2024.
//

#ifndef PRACTICE9_TABLE_H
#define PRACTICE9_TABLE_H
typedef struct {
    long long int_part;
    char char_part;
} Key;

typedef struct {
    Key* keys;
    void** values;
    long long count;
    long long capacity;
} Table;

Table* create_table();
void resize_table(Table* table);
void add_entry(Table* table, long long key_int, char key_char, void* value);
void free_table(Table* table);
#endif //PRACTICE9_TABLE_H
