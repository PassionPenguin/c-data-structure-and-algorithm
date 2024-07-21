//
// Created by Hoarfroster on 21/7/2024.
//

#include <stdio.h>
#include "static-linked-list.h"

int main() {
    StaticLinkedList *list = init();

    insert(list, 0, 10);
    insert(list, 1, 20);
    insert(list, 2, 30);

    printf("Element at index 1: %d\n", get(list, 1)->data);
    printf("Index of value 20: %d\n", indexOf(list, 20));
    printf("Length: %d\n", length(list));
    printf("Capacity: %d\n", size(list));
    printf("Is empty: %d\n", empty(list));

    removeNode(list, 1);
    printf("Element at index 1 after removal: %d\n", get(list, 1)->data);

    clear(list);
    printf("Is empty after clear: %d\n", empty(list));

    destroy(list);

    return 0;
}