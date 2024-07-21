//
// Created by Hoarfroster on 21/7/2024.
//

#include <stdio.h>
#include "sequential-list.h"

int main() {
    SequentialList *list = init();
    insert(list, 0, 10);
    insert(list, 1, 20);
    insert(list, 2, 30);

    int* value = get(list, 1);
    if (value) {
        printf("The element at position 1 is %d\n", *value);
    } else {
        printf("Failed to get element at position 1\n");
    }

    printf("Index of element 20 is %d\n", indexOf(list, 20));

    removeNode(list, 1);
    printf("After removal");

    value = get(list, 1);
    if(value) {
        printf(", the element at position 1 is %d\n", *value);
    } else {
        printf(", failed to get element at position 1\n");
    }

    printf("List length: %d\n", length(list));
    printf("List capacity: %d\n", size(list));

    clear(list);
    printf("List is empty: %d\n", empty(list));

    destroy(list);
    return 0;
}
