#include "headers/tree.h"
#include "headers/exp_stack.h"
#include "headers/postfix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Node_tree *create_node(element *data) {
    Node_tree *newNode = (Node_tree *)malloc(sizeof(Node_tree));
    if (newNode == NULL) {
        printf("Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int is_operator(const element *c) {
    return (c[0] == '+' || c[0] == '*' || c[0] == '/' || c[0] == '^' || (c[0] == '-' && strlen(c) == 1));
}

Node_tree *build_expression_tree(Node_post **head) {
    Node_post *current = *head;
    Node_exp_stack *stack = NULL;

    while (current != NULL) {
        Node_tree *new_node = create_node(current->data);

        if (!is_operator(current->data)) {
            exp_push(&stack, new_node);
        } else {
            new_node->right = exp_pop(&stack);
            new_node->left = exp_pop(&stack);
            exp_push(&stack, new_node);
        }

        current = current->next;
    }

    next_root hlp = exp_pop(&stack);
    return hlp;
}

Trunk* newTrunk(Trunk *prev, char *str) {
    Trunk* trunk = (Trunk*) malloc(sizeof(Trunk));
    trunk->prev = prev;
    trunk->str = strdup(str);
    return trunk;
}

// Функция-помощник для отрисовки веток
void showTrunks(Trunk *p) {
    if (p == NULL) {
        return;
    }

    showTrunks(p->prev);
    printf("%s", p->str);
}

// Функция для красивого отображения
// TO-DO: придумать как двигать ветки при длинных значениях
void display_tree(Node_tree* root, Trunk *prev, int isLeft) {
    if (root == NULL) {
        return;
    }

    char prev_str[6] = "     ";
    Trunk *trunk = newTrunk(prev, prev_str);

    display_tree(root->right, trunk, 1);

    if (!prev) {
        strcpy(trunk->str, "---");
    } else if (isLeft) {
        strcpy(trunk->str, ".---");
        strcpy(prev_str, "    |");
    } else {
        strcpy(trunk->str, "`---");
        strcpy(prev->str, prev_str);
    }

    showTrunks(trunk);
    printf(" %s\n", root->data);

    if (prev) {
        strcpy(prev->str, prev_str);
    }
    strcpy(trunk->str, "    |");

    display_tree(root->left, trunk, 0);
}

void inorder_traversal(Node_tree *root, char *expression, int *index) {
    if (root == NULL)
        return;

    int is_operator = (root->data[0] == '+' || root->data[0] == '-' ||
                       root->data[0] == '*' || root->data[0] == '/');

    if (is_operator)
        expression[(*index)++] = '(';

    inorder_traversal(root->left, expression, index);

    int length = strlen(root->data);
    strncpy(expression + *index, root->data, length);
    *index += length;

    inorder_traversal(root->right, expression, index);

    if (is_operator)
        expression[(*index)++] = ')';
}

char *tree_to_expression(Node_tree *root) {
    if (root == NULL)
        return NULL;

    int max_size = 1000;  // Adjust the size as needed
    char *expression = (char *)malloc(max_size * sizeof(char));
    int index = 0;

    inorder_traversal(root, expression, &index);
    expression[index] = '\0';

    return expression;
}

