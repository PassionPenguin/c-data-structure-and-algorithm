//
// Created by Hoarfroster on 20/7/2024.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct LinkedStack {
    Node *top;
    int length;
} LinkedStack;

// Clear the stack
void clear(LinkedStack *stack) {
    Node *current = stack->top;
    Node *nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    stack->top = NULL;
    stack->length = 0;
}

// Whether the stack is empty
int empty(LinkedStack *stack) {
    return stack->top == NULL;
}

// Length of the stack
int length(LinkedStack *stack) {
    return stack->length;
}

// Initialization
LinkedStack *init() {
    LinkedStack *stack = (LinkedStack *) malloc(sizeof(LinkedStack));
    if(stack == NULL) {
        printf("Failed to allocate memory\n");
        exit(1);
    }

    stack->top = NULL;
    stack->length = 0;
    return stack;
}

// Destroy
void destroy(LinkedStack *stack) {
    clear(stack);
    stack->top = NULL;
    stack->length = 0;
}

// Push an element to the top
int push(LinkedStack *stack, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        return 0; // failed to allocate memory - i.e. stack overflow
    }
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->length++;
    return 1;
}

// Pop the top element
int pop(LinkedStack *stack, int *value) {
    if (stack->top == NULL) {
        return 0; // stack already empty
    }
    Node *temp = stack->top;
    *value = temp->data;
    stack->top = stack->top->next;
    free(temp);
    stack->length--;
    return 1;
}

int main() {
    LinkedStack *stack = init();

    int data[] = {0, 1, 2, 3, 4};
    for (int i = 0; i < 5; i++) {
        if (!push(stack, data[i])) {
            printf("Stackoverflow\n");
        } else {
            printf("Pushed: %d\n", data[i]);
        }
    }

    printf("Length of the stack: %d\n", length(stack));

    int value;
    while (!empty(stack)) {
        pop(stack, &value);
        printf("Popped: %d\n", value);
    }

    destroy(stack);
    return 0;
}
