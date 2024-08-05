//
// Created by Hoarfroster on 21/7/2024.
//

#ifndef C_ALGORITHM_SEQUENTIAL_STACK_H
#define C_ALGORITHM_SEQUENTIAL_STACK_H

#define INITIAL_CAPACITY 10

typedef struct {
    int *data;
    int top;
    int stackSize;
} SequentialStack;

// Clear the stack
void clear(SequentialStack *stack);

// Whether the stack is empty
int empty(SequentialStack *stack);

// Length of the stack
int length(SequentialStack *stack);

// Capacity of the stack
int size(SequentialStack *stack);

// Initialization
SequentialStack *init();

// Destroy
void destroy(SequentialStack *stack);

// Push an element to the top
int push(SequentialStack *stack, int value);

// Pop the top element
int pop(SequentialStack *stack, int *value);

#endif //C_ALGORITHM_SEQUENTIAL_STACK_H
