#include <stdlib.h>
#include <stdio.h>
#include "deck.h"

#define INITIAL_CAPACITY 10



void deck_create(deck* d) {
    d->data = (data_type*)malloc(INITIAL_CAPACITY * sizeof(data_type));
    d->size = 0;
    d->capacity = INITIAL_CAPACITY;
}

bool deck_is_empty(const deck* d) {
    return d->size == 0;
}

void deck_push_front(deck* d, data_type item) {
    if (d->size == d->capacity) {
        d->capacity *= 2;
        d->data = (data_type*)realloc(d->data, d->capacity * sizeof(data_type));
    }
    for (size_t i = d->size; i > 0; i--) {
        d->data[i] = d->data[i - 1];
    }
    d->data[0] = item;
    d->size++;
}

void deck_push_back(deck* d, data_type item) {
    if (d->size == d->capacity) {
        d->capacity *= 2;
        d->data = (data_type*)realloc(d->data, d->capacity * sizeof(data_type));
    }
    d->data[d->size++] = item;
}

void deck_pop_front(deck* d) {
    if (!deck_is_empty(d)) {
        for (size_t i = 0; i < d->size - 1; i++) {
            d->data[i] = d->data[i + 1];
        }
        d->size--;
    }
}

void deck_pop_back(deck* d) {
    if (!deck_is_empty(d)) {
        d->size--;
    }
}

void deck_print(const deck* d) {
    for (size_t i = 0; i < d->size; i++) {
        printf("(%d, %c) ", d->data[i].key, d->data[i].value);
    }
    printf("\n");
}

size_t deck_size(const deck* d) {
    return d->size;
}


void deck_erase(deck* d, const key_type key) {
    for (size_t i = 0; i < d->size; i++) {
        if (d->data[i].key == key) {
            for (size_t j = i; j < d->size - 1; j++) {
                d->data[j] = d->data[j + 1];
            }
            d->size--;
            break;
        }
    }
}

deck* deck_concatenate(deck* d1, deck* d2) {
    deck* result = (deck*)malloc(sizeof(deck));
    deck_create(result);
    for (size_t i = 0; i < d1->size; i++) {
        deck_push_back(result, d1->data[i]);
    }
    for (size_t i = 0; i < d2->size; i++) {
        deck_push_back(result, d2->data[i]);
    }
    return result;
}
