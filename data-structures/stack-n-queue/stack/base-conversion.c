//
// Created by Hoarfroster on 20/7/2024.
//

#include <stdio.h>
#include "linked-stack.h"

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