//
// Created by Hoarfroster on 21/7/2024.
//

#include <stdio.h>
#include "circular-linked-list.h"

int main() {
    CircularLinkedList* list = init();

    insert(list, 0, 10);
    insert(list, 1, 20);
    insert(list, 2, 30);
    printList(list);

    printf("Value at index 1: %d\n", get(list, 1));
    printf("Index of value 20: %d\n", indexOf(list, 20));

    removeNode(list, 1);
    printList(list);

    printf("List empty: %d\n", empty(list));
    printf("List length: %d\n", length(list));

    clear(list);
    printList(list);

    destroy(list);

    return 0;
}