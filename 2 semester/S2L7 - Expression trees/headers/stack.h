#ifndef UNTITLED3_STACK_H
#define UNTITLED3_STACK_H
typedef char next_root;
typedef struct Node_tag {
    next_root value;
    struct Node_tag *next;
} Node_stack;

void push(Node_stack **head, next_root value);
next_root pop(Node_stack **head);
next_root get_value(Node_stack **head);
#endif
