#include "postfix.h"
#include "stack.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef UNTITLED3_UTILS_H
#define UNTITLED3_UTILS_H
#define INITIAL_BUFFER_SIZE 10
typedef enum {
    START,
    SCAN,
    MINUS,
    NUMBER_BEFORE_DOT,
    NUMBER_AFTER_DOT,
    LETTER
} State;

void append_char(char **str, size_t *buffer_size, char c);
void operators_handler(Node_stack **stack_head, Node_post **list_head, State *state, char symbol);
void addition_helper(Node_tree **root, int last_plus);
//Node_tree* addition_helper(Node_tree* root);
void perform_addition(Node_tree **root);
#endif //UNTITLED3_UTILS_H
