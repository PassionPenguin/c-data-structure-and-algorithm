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

// Initialization
LinkedStack *init() {
    LinkedStack *stack = (LinkedStack *) malloc(sizeof(LinkedStack));
    if (stack == NULL) {
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
    Node *newNode = (Node *) malloc(sizeof(Node));
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
    int number;
    printf("Enter the decimal number: ");
    scanf("%d", &number);

    LinkedStack *stack = init();
    while (number) {
        push(stack, number % 2);
        number /= 2;
    }

    printf("The number in binary base is: ");
    while(!empty(stack)) {
        int digit;
        pop(stack, &digit);
        printf("%d", digit);
    }
}