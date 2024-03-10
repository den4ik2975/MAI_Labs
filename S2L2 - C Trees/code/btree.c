#include "btree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uchar.h>

// Создать ноду (
Node* createNode(float value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Положить ноду в дерево (больше вправо(вверх) меньше влево (вниз))
Node* insertNode(Node* root, float value) {
    if (root == NULL) return createNode(value);

    if (value < root->value)
        root->left = insertNode(root->left, value);
    else if (value > root->value)
        root->right = insertNode(root->right, value);

    return root;
}

// Проверка на наличие ноды с заданным значением в дереве
bool nodeExists(Node* root, float value) {
    if (root == NULL){
        return false;}
    if (root->value == value)
        return true;
    if (value < root->value)
        return nodeExists(root->left, value);
    else
        return nodeExists(root->right, value);
}


// Функция-помощник для создания веток
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
void displayTree(Node* root, Trunk *prev, int isLeft) {
    if (root == NULL) {
        return;
    }

    char prev_str[7] = "      ";
    Trunk *trunk = newTrunk(prev, prev_str);

    displayTree(root->right, trunk, 1);

    if (!prev) {
        strcpy(trunk->str, "---");
    } else if (isLeft) {
        strcpy(trunk->str, ".---");
        strcpy(prev_str, "     |");
    } else {
        strcpy(trunk->str, "`---");
        strcpy(prev->str, prev_str);
    }

    showTrunks(trunk);
    printf(" %.2f\n", root->value);

    if (prev) {
        strcpy(prev->str, prev_str);
    }
    strcpy(trunk->str, "     |");

    displayTree(root->left, trunk, 0);
}


// Найти ноду с минимальным значением (нужно для удаления)
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

// Удалить ноду из дерева
Node* deleteNode(Node* root, float value) {
    if (root == NULL) return root;

    if (value < root->value)
        root->left = deleteNode(root->left, value);
    else if (value > root->value)
        root->right = deleteNode(root->right, value);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = minValueNode(root->right);
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->value);
    }
    return root;
}

// Проверка на Би))
bool isBTree(Node* root) {
    if (root == NULL) return true;
    if (root->left == NULL && root->right == NULL) return true;
    if (root->left != NULL && root->right != NULL)
        return isBTree(root->left) && isBTree(root->right);

    return false;
}
