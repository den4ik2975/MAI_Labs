#include "headers/postfix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node_post* createNode(const char *data) {
    Node_post *newNode = (Node_post*)malloc(sizeof(Node_post));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = strdup(data);  // Копируем строку
    newNode->next = NULL;
    return newNode;
}

// Функция для добавления элемента в конец списка
void append(Node_post **head, const char *data) {
    Node_post *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node_post *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Функция для освобождения памяти, выделенной под список
void freeList(Node_post *head) {
    while (head != NULL) {
        Node_post *temp = head;
        head = head->next;
        free(temp->data); // Освобождаем память, выделенную под строку
        free(temp);       // Освобождаем память, выделенную под узел
    }
}
