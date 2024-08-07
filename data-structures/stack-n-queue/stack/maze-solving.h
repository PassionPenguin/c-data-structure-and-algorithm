//
// Created by Hoarfroster on 21/7/2024.
//

#ifndef C_ALGORITHM_MAZE_SOLVING_H
#define C_ALGORITHM_MAZE_SOLVING_H

typedef struct Node {
    int x;
    int y;
    int fromDirection; // 1 - from left, 2 - from top, 3 - from right, 4 - from bottom
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
int push(LinkedStack *stack, int position, int type, int fromDirection);

// Pop the top element
int pop(LinkedStack *stack);

#endif //C_ALGORITHM_MAZE_SOLVING_H
