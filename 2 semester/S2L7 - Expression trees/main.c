#include "headers/stack.h"
#include "headers/utils.h"
#include "headers/postfix.h"
#include "headers/tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void main() {
    Node_stack *postfix_stack = NULL;
    Node_post *postfix_list = NULL;
    State state = START;
    char symbol;
    size_t buffer_size = INITIAL_BUFFER_SIZE;
    char *current_str = (char *)malloc((buffer_size + 1) * sizeof(char));
    current_str[0] = '\0';

    while ((symbol = getchar()) != '\n'){
        switch (state) {
            case START:
            case SCAN:
                if (isdigit(symbol)) {
                    append_char(&current_str, &buffer_size, symbol);
                    state = NUMBER_BEFORE_DOT;
                } else if (isalpha(symbol)) {
                    append_char(&current_str, &buffer_size, symbol);
                    state = LETTER;
                } else if (symbol == '-') {
                    append_char(&current_str, &buffer_size, symbol);
                    state = MINUS;
                } else if (symbol == ')') {
                    while (get_value(&postfix_stack) != '(') {
                        char temp_operator[2] = {pop(&postfix_stack), '\0' };
                        append(&postfix_list, temp_operator);
                    }
                    pop(&postfix_stack);
                    state = SCAN;
                } else if (symbol == ' ') {
                    state = SCAN;
                } else if (symbol == '(') {
                    push(&postfix_stack, symbol);
                } else {
                    operators_handler(&postfix_stack, &postfix_list, &state, symbol);
                }
                break;

            case NUMBER_BEFORE_DOT:
                if (isdigit(symbol)) {
                    append_char(&current_str, &buffer_size, symbol);
                    state = NUMBER_BEFORE_DOT;
                } else if (isalpha(symbol)) {
                    append_char(&current_str, &buffer_size, symbol);
                    state = LETTER;
                } else if (symbol == '.') {
                    append_char(&current_str, &buffer_size, symbol);
                    state = NUMBER_AFTER_DOT;
                } else if (symbol == ' ') {
                    append(&postfix_list, current_str);
                    current_str[0] = '\0';
                    state = SCAN;
                } else if (symbol == ')') {
                    append(&postfix_list, current_str);
                    current_str[0] = '\0';
                    while (get_value(&postfix_stack) != '(') {
                        char temp_operator[2] = {pop(&postfix_stack), '\0' };
                        append(&postfix_list, temp_operator);
                    }
                    pop(&postfix_stack);
                    state = SCAN;
                } else if (symbol == '(') {
                    append(&postfix_list, current_str);
                    current_str[0] = '\0';
                    push(&postfix_stack, symbol);
                } else {
                    append(&postfix_list, current_str);
                    current_str[0] = '\0';
                    operators_handler(&postfix_stack, &postfix_list, &state, symbol);
                }
                break;

            case NUMBER_AFTER_DOT:
                if (isdigit(symbol)) {
                    append_char(&current_str, &buffer_size, symbol);
                    state = NUMBER_AFTER_DOT;
                } else if (isalpha(symbol)) {
                    append_char(&current_str, &buffer_size, symbol);
                    state = LETTER;
                } else if (symbol == ' ') {
                    append(&postfix_list, current_str);
                    current_str[0] = '\0';
                    state = SCAN;
                } else if (symbol == ')') {
                    append(&postfix_list, current_str);
                    current_str[0] = '\0';
                    while (get_value(&postfix_stack) != '(') {
                        char temp_operator[2] = {pop(&postfix_stack), '\0' };
                        append(&postfix_list, temp_operator);
                    }
                    pop(&postfix_stack);
                } else if (symbol == '(') {
                    append(&postfix_list, current_str);
                    current_str[0] = '\0';
                    push(&postfix_stack, symbol);
                } else {
                    append(&postfix_list, current_str);
                    current_str[0] = '\0';
                    operators_handler(&postfix_stack, &postfix_list, &state, symbol);
                }
                break;

            case MINUS:
                if (isdigit(symbol)) {
                    append_char(&current_str, &buffer_size, symbol);
                    state = NUMBER_BEFORE_DOT;
                } else if (isalpha(symbol)) {
                    append_char(&current_str, &buffer_size, symbol);
                    state = LETTER;
                } else {
                    current_str[0] = '\0';
                    operators_handler(&postfix_stack, &postfix_list, &state, '-');

                    if (symbol == ' ') {
                        state = SCAN;
                    } else if (symbol == '(') {
                        push(&postfix_stack, symbol);
                        state = SCAN;
                    } else {
                        exit(0);
                    }

                }
                break;

            case LETTER:
                if (isalpha(symbol)) {
                    append_char(&current_str, &buffer_size, symbol);
                    state = LETTER;
                } else if (symbol == ' ') {
                    append(&postfix_list, current_str);
                    current_str[0] = '\0';
                    state = SCAN;
                } else if (symbol == ')') {
                    append(&postfix_list, current_str);
                    current_str[0] = '\0';
                    while (get_value(&postfix_stack) != '(') {
                        char temp_operator[2] = {pop(&postfix_stack), '\0' };
                        append(&postfix_list, temp_operator);
                    }
                    pop(&postfix_stack);
                    state = SCAN;
                } else if (symbol == '(') {
                    append(&postfix_list, current_str);
                    current_str[0] = '\0';
                    push(&postfix_stack, symbol);
                } else {
                    append(&postfix_list, current_str);
                    current_str[0] = '\0';
                    operators_handler(&postfix_stack, &postfix_list, &state, symbol);
                }
                break;
        }
    }
    if (strlen(current_str) != 0) {
        append(&postfix_list, current_str);
    }

    while (get_value(&postfix_stack) != 'l'){
        char temp_operator[2] = {pop(&postfix_stack), '\0'};
        append(&postfix_list, temp_operator);
    }

    Node_tree *exp_root = build_expression_tree(&postfix_list);
    display_tree(exp_root, NULL, 0);
    perform_addition(&exp_root);
    printf("\n\n");
    display_tree(exp_root, NULL, 0);
    char* ans = tree_to_expression(exp_root);
    printf("Expression: %s\n", ans);
}
