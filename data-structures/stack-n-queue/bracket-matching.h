//
// Created by Hoarfroster on 21/7/2024.
//

#ifndef C_ALGORITHM_BRACKET_MATCHING_H
#define C_ALGORITHM_BRACKET_MATCHING_H

#define LEFT_PARENTHESES 1
#define RIGHT_PARENTHESES 2
#define LEFT_CURLY_BRACKETS 3
#define RIGHT_CURLY_BRACKETS 4
#define LEFT_SQUARE_BRACKETS 5
#define RIGHT_SQUARE_BRACKETS 6

typedef struct Node {
    int position;
    int type;
    struct Node *next;
} Node;

typedef struct LinkedStack {
    Node *top;
    int length;
} LinkedStack;

typedef struct {
    int leftType;
    int rightType;
    int leftPosition;
    int rightPosition;
} MatchedBrackets;

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
int push(LinkedStack *stack, int position, int type);

// Pop the top element
int pop(LinkedStack *stack);

#endif //C_ALGORITHM_BRACKET_MATCHING_H
