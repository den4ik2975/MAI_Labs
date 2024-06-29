#include "deck.h"
#include <stdlib.h>


deck* quickSort(deck* d) {
    if (d->size <= 1) {
        return d;
    }

    deck* left = (deck*)malloc(sizeof(deck));
    deck_create(left);
    deck* right = (deck*)malloc(sizeof(deck));
    deck_create(right);

    data_type pivot = d->data[0];

    for (size_t i = 1; i < d->size; i++) {
        if (d->data[i].key < pivot.key) {
            deck_push_back(left, d->data[i]);
        } else {
            deck_push_back(right, d->data[i]);
        }
    }

    deck* sorted_left = quickSort(left);
    deck* sorted_right = quickSort(right);


    deck_push_back(sorted_left, pivot);
    deck* final_result = deck_concatenate(sorted_left, sorted_right);

    free(sorted_left);
    free(sorted_right);

    return final_result;
}



