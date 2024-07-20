//
// Created by Hoarfroster on 20/7/2024.
//

#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 10

typedef struct {
    int *data;
    int top;
    int stackSize;
} SequentialStack;

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

int main() {
    SequentialStack *stack = init();

    int data[] = {0, 1, 2, 3, 4};
    for (int i = 0; i < 5; i++) {
        if (!push(stack, data[i])) {
            printf("Stackoverflow\n");
        } else {
            printf("Pushed: %d\n", data[i]);
        }
    }

    printf("Length of the stack: %d\n", length(stack));
    printf("Capacity of the stack: %d\n", size(stack));

    int value;
    while (!empty(stack)) {
        pop(stack, &value);
        printf("Popped: %d\n", value);
    }

    clear(stack);
    destroy(stack);

    return 0;
}
