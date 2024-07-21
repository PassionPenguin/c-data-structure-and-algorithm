//
// Created by Hoarfroster on 21/7/2024.
//

#include <stdio.h>
#include "sequential-stack.h"

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