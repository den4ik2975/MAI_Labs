#include "postfix.h"

#ifndef UNTITLED3_TREE_H
#define UNTITLED3_TREE_H
typedef char element;
typedef struct Node_tree {
    element *data;
    struct Node_tree *left;
    struct Node_tree *right;
} Node_tree;

typedef struct Trunk {
    struct Trunk *prev;
    char *str;
} Trunk;

int is_operator(const element *c);
Node_tree *create_node(element *data);
Node_tree *build_expression_tree(Node_post **head);
void display_tree(Node_tree* root, Trunk *prev, int isLeft);
void inorder_traversal(Node_tree *root, char *expression, int *index);
char *tree_to_expression(Node_tree *root);
#endif //UNTITLED3_TREE_H
