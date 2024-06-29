#include "headers/stack.h"
#include <stdio.h>
#include <stdlib.h>

#define STACK_OVERFLOW  (-100)
#define STACK_UNDERFLOW (-101)
#define OUT_OF_MEMORY   -102

void push(Node_stack **head, next_root value) {
    Node_stack *tmp = malloc(sizeof(Node_stack));
    if (tmp == NULL) {
        exit(STACK_OVERFLOW);
    }
    tmp->next = *head;
    tmp->value = value;
    *head = tmp;
}


next_root pop(Node_stack **head) {
    Node_stack *out;
    next_root value;
    if (*head == NULL) {
        exit(STACK_UNDERFLOW);
    }
    out = *head;
    *head = (*head)->next;
    value = out->value;
    free(out);
    return value;
}


next_root get_value(Node_stack **head) {
    Node_stack *last;
    last = *head;

    if (last == NULL) {
        return 'l';
    }
    return last->value;
}
