#ifndef UNTITLED3_POSTFIX_H
#define UNTITLED3_POSTFIX_H
typedef char element;
typedef struct Node_post {
    element *data;
    struct Node_post *next;
} Node_post;

void freeList(Node_post *head);
void append(Node_post **head, const char *data);
Node_post* createNode(const char *data);

#endif //UNTITLED3_POSTFIX_H
