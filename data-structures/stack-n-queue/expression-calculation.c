//
// Created by Hoarfroster on 22/7/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "expression-calculation.h"

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
int push(LinkedStack *stack, int value) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
        return 0; // failed to allocate memory - i.e. stack overflow
    }
    newNode->value = value;
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

// returns 0 if no precedence, 1 if leftOpr > rightOpr, -1 if leftOpr < rightOpr
int precedence(int leftOpr, int rightOpr) {
    // optimized switch table
    switch (leftOpr) {
        case '+':
        case '-':
            switch (rightOpr) {
                case '+':
                case '-':
                case ')':
                    return 1;
                case '*':
                case '/':
                case '(':
                    return -1;
                default:
                    printf("Unknown operator %c", rightOpr);
                    exit(1);
            }
        case '*':
        case '/':
            switch (rightOpr) {
                case '+':
                case '-':
                case '*':
                case '/':
                case ')':
                    return 1;
                case '(':
                    return -1;
                default:
                    printf("Unknown operator %c", rightOpr);
                    exit(1);
            }
        case '(':
            switch (rightOpr) {
                case '+':
                case '-':
                case '*':
                case '/':
                case '(':
                    return -1;
                case ')':
                    return 0;
                default:
                    printf("Unknown operator %c", rightOpr);
                    exit(1);
            }
        case ')':
            if (rightOpr == '(') break;
            return 1;
        default:
            printf("Unknown operator %c", rightOpr);
            exit(1);
    }

    printf("Unknown operator %c", rightOpr);
    exit(1);
}

int operate(LinkedStack *operators, LinkedStack *operands) {
    int rightOperand = operands->top->value;
    pop(operands);
    int leftOperand = operands->top->value;
    pop(operands);
    int operator = operators->top->value;
    pop(operators);

    printf("Calculating: %d %c %d\n", leftOperand, operator, rightOperand);

    switch (operator) {
        case '+':
            return leftOperand + rightOperand;
        case '-':
            return leftOperand - rightOperand;
        case '*':
            return leftOperand * rightOperand;
        case '/':
            return leftOperand / rightOperand;
        default:
            printf("Unknown operator %c", operator);
            exit(1);
    }
}

int calculate(const char expression[], int size) {
    LinkedStack *operators = init(), *operands = init();

    int isOperand = 0;
    for (int i = 0; i < size; i++) {
        char c = expression[i];
        if (c >= '0' && c <= '9') {
            if (isOperand) {
                operands->top->value = operands->top->value * 10 + (c - '0');
            } else {
                isOperand = 1;
                push(operands, c - '0');
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
            isOperand = 0;
            if (empty(operators)) {
                push(operators, c);
            } else {
                if (precedence(operators->top->value, c) == -1) {
                    push(operators, c);
                } else {
                    int delimiter_used = 0, mark = 1;
                    while (!empty(operators) && mark) {
                        // check if the top operator in `operators` precedes `c`
                        switch (precedence(operators->top->value, c)) {
                            case 1: // if so, calculate **opr `operators->top` opr**
                                if (operators->top->value == '(') break;
                                push(operands, operate(operators, operands));
                                continue;
                            case 0: // de-bracketed
                                if (delimiter_used) {
                                    mark = 0;
                                } else {
                                    pop(operators);
                                    delimiter_used = 1;
                                }
                                break;
                            case -1: // else push `c` to `operators`
                                push(operators, c);
                                mark = 0;
                                break;
                        }
                    }

                    if (empty(operators) && c != '(' && c != ')') {
                        push(operators, c);
                    }
                }
            }
        }
    }

    while (!empty(operators)) {
        push(operands, operate(operators, operands));
    }

    int result = operands->top->value;
    pop(operands);
    if (!empty(operands)) {
        exit(1); // more than one operand left. should be an error
    }

    destroy(operators);
    destroy(operands);

    return result;
}

int main() {
    char expression1[] = "9+10*(5-(6/2))+2/2+4", expression1Size = 21;
    printf("Result of expression %s is %d", expression1, calculate(expression1, expression1Size));

    char expression2[] = "20*5+(3-(5*2+2/1*2+2*(4/2)+1)+55/11-3)+2", expression2Size = 40;
    printf("Result of expression %s is %d", expression2, calculate(expression2, expression2Size));
}