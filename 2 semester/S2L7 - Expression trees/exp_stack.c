#include "headers/exp_stack.h"
#include <stdlib.h>

#define STACK_OVERFLOW  (-100)
#define STACK_UNDERFLOW (-101)
#define OUT_OF_MEMORY   -102

void exp_push(Node_exp_stack **head, next_root value) {
    Node_exp_stack *tmp = malloc(sizeof(Node_exp_stack));
    if (tmp == NULL) {
        exit(STACK_OVERFLOW);
    }
    tmp->next = *head;
    tmp->value = value;
    *head = tmp;
}


next_root exp_pop(Node_exp_stack **head) {
    Node_exp_stack *out;
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


