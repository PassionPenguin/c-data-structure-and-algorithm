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

// returns 1 if precedence `>=`, 0 if `<`
int precedence(int leftOpr, int rightOpr) {
    // optimized switch table
    switch (leftOpr) {
        case '+':
        case '-':
            return (rightOpr == '+' || rightOpr == '-') ? 1 : 0;
        case '*':
        case '/':
            return (rightOpr == '*' || rightOpr == '/' || rightOpr == '+' || rightOpr == '-') ? 1 : 0;
        default:
            printf("Unknown operator %c", leftOpr);
            exit(1);
    }
}

void operate(LinkedStack *operators, LinkedStack *operands) {
    int rightOperand = operands->top->value;
    pop(operands);
    int leftOperand = operands->top->value;
    pop(operands);
    int operator = operators->top->value;
    pop(operators);

    printf("Calculating: %d %c %d\n", leftOperand, operator, rightOperand);

    int result;
    switch (operator) {
        case '+':
            result = leftOperand + rightOperand;
            break;
        case '-':
            result = leftOperand - rightOperand;
            break;
        case '*':
            result = leftOperand * rightOperand;
            break;
        case '/':
            result = leftOperand / rightOperand;
            break;
        default:
            printf("Unknown operator %c", operator);
            exit(1);
    }

    push(operands, result);
}

int isDigit(int x) {
    return x >= '0' && x <= '9';
}

int calculate(const char expression[], int size) {
    LinkedStack *operators = init(), *operands = init();

    for (int i = 0; i < size; i++) {
        char c = expression[i];
        if (isDigit(c)) {
            int x = 0, j = i;
            while(j < size && isDigit(expression[j])) x = x * 10 + (expression[j++] - '0'); // continue pushing number until non-numeric char found
            i = j - 1;
            push(operands, x);
        } else if (c == '(') {
            push(operators, '(');
        } else if (c == ')') {
            while(operators->top->value != '(') operate(operators, operands);
            pop(operators); // pop the left parenthesis
        } else {
            while(!empty(operators) && operators->top->value != '(' && precedence(operators->top->value, c) > 0) operate(operators, operands);
            push(operators, c);
        }
    }
    while(!empty(operators)) operate(operators, operands);

    int result = operands->top->value;

    destroy(operators);
    destroy(operands);

    return result;
}

int main() {
    char expression1[] = "9+10*(5-(6/2))+2/2+4", expression1Size = 20;
    printf("Result of expression %s is %d\n\n", expression1, calculate(expression1, expression1Size));

    char expression2[] = "20*5+(3-(5*2+2/1*2+2*(4/2)+1)+55/11-3)+2", expression2Size = 40;
    printf("Result of expression %s is %d", expression2, calculate(expression2, expression2Size));
}