#include "tree.h"
#ifndef UNTITLED3_EXP_STACK_H
#define UNTITLED3_EXP_STACK_H
typedef Node_tree *next_root;
typedef struct Node_tag {
    next_root value;
    struct Node_tag *next;
} Node_exp_stack;

void exp_push(Node_exp_stack **head, next_root value);
next_root exp_pop(Node_exp_stack **head);
#endif //UNTITLED3_EXP_STACK_H
