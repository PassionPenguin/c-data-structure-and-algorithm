//
// Created by Hoarfroster on 21/7/2024.
//

#ifndef C_ALGORITHM_LINKED_STACK_H
#define C_ALGORITHM_LINKED_STACK_H

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct LinkedStack {
    Node *top;
    int length;
} LinkedStack;

// Clear the stack
void clear(LinkedStack *stack);

// Whether the stack is empty
int empty(LinkedStack *stack);

// Length of the stack
int length(LinkedStack *stack);

// Initialization
LinkedStack *init();

// Destroy
void destroy(LinkedStack *stack);

// Push an element to the top
int push(LinkedStack *stack, int value);

// Pop the top element
int pop(LinkedStack *stack, int *value);

#endif //C_ALGORITHM_LINKED_STACK_H
