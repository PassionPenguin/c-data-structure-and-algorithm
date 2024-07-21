//
// Created by Hoarfroster on 21/7/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "bracket-matching.h"

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
int push(LinkedStack *stack, int position, int type) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
        return 0; // failed to allocate memory - i.e. stack overflow
    }
    newNode->position = position;
    newNode->type = type;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->length++;
    return 1;
}

// Pop the top element
int pop(LinkedStack *stack) {
    if (stack->top == NULL) {
        return 0; // stack already empty
    }
    Node *temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    stack->length--;
    return 1;
}

void printMatchedBrackets(MatchedBrackets *matchedBrackets) {
    printf("Matched brackets %d (type %d) and %d (type %d).\n", matchedBrackets->leftPosition,
           matchedBrackets->leftType, matchedBrackets->rightPosition, matchedBrackets->rightType);
}

void matchRightBracket(LinkedStack *stack, int leftType, int rightType, int position) {
    Node *topNode = stack->top;
    if (topNode == NULL) {
        printf("No left bracket to match.\n");
        exit(1);
    } else {
        if (topNode->type == leftType) {
            MatchedBrackets *matchedBrackets = (MatchedBrackets *) malloc(sizeof(MatchedBrackets));
            matchedBrackets->leftType = leftType;
            matchedBrackets->rightType = rightType;
            matchedBrackets->leftPosition = topNode->position;
            matchedBrackets->rightPosition = position;
            printMatchedBrackets(matchedBrackets);
            pop(stack);
        } else {
            printf("Unmatched bracket (type %d) found at position %d. Bracket should be of type %d.\n", topNode->type,
                   topNode->position, rightType);
            exit(1);
        }
    }
}

void matchBracket(int *data, int length) {
    LinkedStack *stack = init();
    for (int i = 0; i < length; i++) {
        // push left brackets to the stack
        switch (data[i]) {
            case LEFT_PARENTHESES:
            case LEFT_CURLY_BRACKETS:
            case LEFT_SQUARE_BRACKETS:
                push(stack, i, data[i]);
                break;
            case RIGHT_PARENTHESES:
                matchRightBracket(stack, LEFT_PARENTHESES, RIGHT_PARENTHESES, i);
                break;
            case RIGHT_CURLY_BRACKETS:
                matchRightBracket(stack, LEFT_CURLY_BRACKETS, RIGHT_CURLY_BRACKETS, i);
                break;
            case RIGHT_SQUARE_BRACKETS:
                matchRightBracket(stack, LEFT_SQUARE_BRACKETS, RIGHT_SQUARE_BRACKETS, i);
                break;
            default:
                printf("Invalid bracket type\n");
                exit(1);
        }
    }

    if (!empty(stack)) {
        while (!empty(stack)) {
            Node *topNode = stack->top;
            printf("Unmatched bracket (type %d) at position %d.\n", topNode->type, topNode->position);
            pop(stack);
        }
    }

    destroy(stack);
}

int main() {
    printf("Example of validated data:\n");
    int validatedData[] = {LEFT_SQUARE_BRACKETS, LEFT_PARENTHESES, LEFT_CURLY_BRACKETS, RIGHT_CURLY_BRACKETS,
                           LEFT_PARENTHESES, RIGHT_PARENTHESES, RIGHT_PARENTHESES, RIGHT_SQUARE_BRACKETS};
    matchBracket(validatedData, 8);

    printf("Example of a data missing a bracket:\n");
    int missingBracketData[] = {LEFT_SQUARE_BRACKETS, LEFT_PARENTHESES, LEFT_CURLY_BRACKETS, RIGHT_CURLY_BRACKETS,
                                LEFT_PARENTHESES, RIGHT_PARENTHESES, RIGHT_PARENTHESES};
    matchBracket(missingBracketData, 7);

    printf("Example of a data containing a unmatched bracket:\n");
    int unmatchedBracketData[] = {LEFT_SQUARE_BRACKETS, LEFT_PARENTHESES, LEFT_CURLY_BRACKETS, RIGHT_PARENTHESES,
                                  LEFT_PARENTHESES, RIGHT_PARENTHESES, RIGHT_PARENTHESES, RIGHT_SQUARE_BRACKETS};
    matchBracket(unmatchedBracketData, 8);

    return 0; // though if the test goes well, this line will never be reached as error will be thrown.
}