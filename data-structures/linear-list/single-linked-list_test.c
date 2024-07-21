//
// Created by Hoarfroster on 21/7/2024.
//

#include <stdio.h>
#include "single-linked-list.h"

int main() {
    LinkedList *list = init();

    insert(list, 0, 10);
    insert(list, 1, 20);
    insert(list, 2, 30);
    printList(list);

    Node* value = get(list, 1);
    if (value) {
        printf("The element at position 1 is %d\n", value->data);
    } else {
        printf("Failed to get element at position 1\n");
    }
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