#ifndef BTREE_H
#define BTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Структура нод и веток
typedef struct Node {
    float value;
    struct Node *left, *right;
} Node;

typedef struct Trunk {
    struct Trunk *prev;
    char *str;
} Trunk;


Node* createNode(float value);
Node* insertNode(Node* root, float value);
bool nodeExists(Node* root, float value);
Trunk* newTrunk(Trunk *prev, char *str);
void showTrunks(Trunk *p);
void displayTree(Node* root, Trunk *prev, int isLeft);
Node* minValueNode(Node* node);
Node* deleteNode(Node* root, float value);
bool isBTree(Node* root);


#endif
