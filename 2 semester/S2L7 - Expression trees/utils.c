#include "headers/utils.h"
#include "headers/postfix.h"
#include "headers/stack.h"
#include "headers/tree.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void append_char(char **str, size_t *buffer_size, char c) {
    size_t length = strlen(*str);

    if (length >= *buffer_size - 1) {
        *buffer_size *= 2;
        *str = (char *)realloc(*str, *buffer_size * sizeof(char));
        if (*str == NULL) {
            printf("Memory reallocation failed\n");
            return;
        }
    }

    (*str)[length] = c;
    (*str)[length + 1] = '\0';
}

void operators_handler(Node_stack **stack_head, Node_post **list_head, State *state, char symbol) {
    if (symbol == '^') {
        push(stack_head, symbol);
    } else if (symbol == '*' || symbol == '/') {
        while (get_value(stack_head) == '^') {
            char temp_operator[2] = { pop(stack_head), '\0' };
            append(list_head, temp_operator);
        }
        push(stack_head, symbol);
    } else if (symbol == '+' || symbol == '-') {
        while (get_value(stack_head) == '^' || get_value(stack_head) == '*' || get_value(stack_head) == '/') {
            char temp_operator[2] = { pop(stack_head), '\0' };
            append(list_head, temp_operator);
        }
        push(stack_head, symbol);
    } else {
        exit(0);
    }
    *state = SCAN;
}

int is_minus_or_plus(const char *c) {
    return (c[0] == '+' || (c[0] == '-' && strlen(c) == 1));
}

int is_other_operator(const char *c) {
    return (c[0] == '*' || c[0] == '/' || c[0] == '^');
}

int is_number(const char *str) {
    while (*str) {
        if (!isdigit(*str))
            return 0;
        str++;
    }
    return 1;
}

void perform_addition(Node_tree **root) {
    if (is_minus_or_plus((*root)->data)) {
        addition_helper(root, 1);
        return;
    }
    if ((*root)->left != NULL && is_minus_or_plus((*root)->left->data)) {
        addition_helper(&((*root)->left), 1);
    } else if ((*root)->left != NULL) {
        perform_addition(&(*root)->left);
    }
    if ((*root)->right != NULL && is_minus_or_plus((*root)->right->data)) {
        addition_helper(&((*root)->right), 1);
    } else if ((*root)->right != NULL) {
        perform_addition(&(*root)->right);
    }
}

void addition_helper(Node_tree **root, int last_plus) {
    double buffer = 0;
    int from_swap = 0; // from right or left. Right 1 Left 2
    int side = 0; // right 1 left 2
    char *endptr = "";
    Node_tree *last = *root;
    Node_tree *current = *root;

    if (current->left == NULL && current->right == NULL) {
        return;
    }
    // Searching for first suitable node
    if (last_plus) {
        buffer += strtod(current->left->data, &endptr);
        if (strcmp(endptr, "") != 0){
            if (current->data[0] == '+') { last_plus = 1; } else { last_plus = 0; }

            if (is_minus_or_plus(current->left->data)) {
                addition_helper(&current->left, last_plus);
            } else if (is_other_operator(current->left->data)) {
                perform_addition(&current->left);
            }

            if (is_minus_or_plus(current->right->data)) {
                addition_helper(&current->right, last_plus);
            } else if (is_other_operator(current->right->data)) {
                perform_addition(&current->right);
            }

            return;
        }

    } else {
        if (current->data[0] == '+') { last_plus = 1; } else { last_plus = 0; }
        if (is_minus_or_plus(current->left->data)) {
            addition_helper(&current->left, last_plus);
        } else if (is_other_operator(current->left->data)) {
            perform_addition(&current->left);
        }

        if (is_minus_or_plus(current->right->data)) {
            addition_helper(&current->right, last_plus);
        } else if (is_other_operator(current->right->data)) {
            perform_addition(&current->right);
        }

        return;
    }
    buffer = 0;
    endptr = "";
    //Searching for addable nodes
    while (1) {
        if (last_plus == 1) {
            if (!is_operator(current->data)) {
                buffer += strtod(current->data, &endptr);
                if (strcmp(endptr, "") == 0) {
                    if (*root == last) {
                        sprintf((*root)->data, "%f", buffer);
                        (*root)->right=NULL;
                        (*root)->left=NULL;
                        return;
                    } else {
                        last->data = last->left->data;
                        last->right = last->left->right;
                        last->left = last->left->left;
                    }
                    break;
                } else {
                    endptr = "";
                    break;
                }
            }

            if (current->data[0] == '+') { last_plus = 1; } else last_plus = 0;

            if (is_other_operator(current->left->data)) {
                perform_addition(&(current->left));
                last = current;
            } else if (is_minus_or_plus(current->left->data)) {
                addition_helper(&(current->left), 1);
                last = current;
            } else {
                buffer += strtod(current->left->data, &endptr);
                if (strcmp(endptr, "") == 0) {
                    if (last != NULL) {
                        last->right = current->right;
                        last->data = current->data;
                    }
                } else {
                    endptr = "";
                    last = current;
                }
            }

            if (is_other_operator(current->right->data)) {
                perform_addition(&(current->right));
            } else {
                current = current->right;
                continue;
            }

        } else {
            if (!is_operator(current->data)) {
                break;
            }

            if (current->data[0] == '+') { last_plus = 1; } else last_plus = 0;

            if (is_other_operator(current->left->data)) {
                perform_addition(&(current->left));
            } else if (is_minus_or_plus(current->left->data)) {
                addition_helper(&(current->left), last_plus);
            } else {
                last = current;
            }

            if (is_other_operator(current->right->data)) {
                perform_addition(&(current->right));
            } else {
                current = current->right;
                continue;
            }
        }
    }
    sprintf((*root)->left->data, "%f", buffer);
}