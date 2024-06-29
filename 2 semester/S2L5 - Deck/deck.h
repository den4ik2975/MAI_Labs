//
// Created by den41 on 01.05.2024.
//

#ifndef LABWORK26_deckK_H
#define LABWORK26_deckK_H
#ifndef _deck_H_
#define _deck_H_

#include <stdbool.h>
#include <stddef.h>

typedef int key_type;
typedef char value_type;

typedef struct {
    key_type key;
    value_type value;
} data_type;

typedef struct {
    data_type* data;
    size_t size;
    size_t capacity;
} deck;

void deck_create(deck*);
bool deck_is_empty(const deck*);
void deck_push_front(deck*, data_type);
void deck_push_back(deck*, data_type);
void deck_pop_front(deck*);
void deck_pop_back(deck*);
void deck_print(const deck*);
size_t deck_size(const deck*);
void deck_insert(deck*, const data_type);
void deck_erase(deck*, const key_type);
deck* deck_concatenate(deck*, deck*);

#endif


#endif //LABWORK26_deckK_H
