//
// Created by Hoarfroster on 20/7/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "sequential-stack.h"

// Clear the stack
void clear(SequentialStack *stack) {
    stack->top = -1;
}

// Whether the stack is empty
int empty(SequentialStack *stack) {
    return stack->top == -1;
}

// Length of the stack
int length(SequentialStack *stack) {
    return stack->top + 1;
}

// Capacity (size) of the stack
int size(SequentialStack *stack) {
    return stack->stackSize;
}

// Initialization
SequentialStack *init() {
    SequentialStack *stack = (SequentialStack *) malloc(sizeof(SequentialStack));
    if (stack == NULL) {
        printf("Failed to allocate memory\n");
        exit(1);
    }

    stack->data = (int *) malloc(INITIAL_CAPACITY * sizeof(int));
    if (stack->data == NULL) {
        printf("Failed to allocate memory\n");
        exit(1);
    }

    clear(stack);
    stack->stackSize = INITIAL_CAPACITY;
    return stack;
}

// Destroy
void destroy(SequentialStack *stack) {
    free(stack->data);
    stack->data = NULL;
    stack->top = -1;
    stack->stackSize = 0;
}

// Push an element to the top
int push(SequentialStack *stack, int value) {
    if (stack->top == stack->stackSize - 1) {
        int newCapacity = stack->stackSize * 2;
        int *newData = (int *) realloc(stack->data, newCapacity * sizeof(int));
        if (newData == NULL) return 0; // failed to allocate memory - stack overflow
        stack->data = newData;
        stack->stackSize = newCapacity;
    }
    stack->data[++stack->top] = value;
    return 1;
}

// Pop the top element
int pop(SequentialStack *stack, int *value) {
    if (stack->top == -1) return 0;
    *value = stack->data[stack->top--];
    return 1;
}
