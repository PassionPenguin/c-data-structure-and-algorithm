//
// Created by Hoarfroster on 20/7/2024.
//

#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 10
#define NULL_INDEX (-1)

typedef struct {
    int data;
    int next;
} Node;

typedef struct {
    Node nodes[INITIAL_CAPACITY];
    int head;
    int free;
    int length;
    int listSize;
} StaticLinkedList;

// Clear the list
void clear(StaticLinkedList *list) {
    // chain all nodes to a free linked list
    for (int i = 0; i < list->listSize - 1; i++) {
        list->nodes[i].next = i + 1;
    }
    list->nodes[list->listSize - 1].next = NULL_INDEX; // marking the end of the free linked list
}

// Whether the list is empty
int empty(StaticLinkedList *list) {
    return list->length == 0;
}

// Length of the list
int length(StaticLinkedList *list) {
    return list->length;
}

// Capacity (size) of the list
int size(StaticLinkedList *list) {
    return list->listSize;
}

// Initialization
StaticLinkedList *init() {
    StaticLinkedList *list = (StaticLinkedList *) malloc(sizeof(StaticLinkedList));
    // point the actual linked list to be an empty one
    list->head = NULL_INDEX;
    // point the free linked list to start at index 0
    // i.e. list->nodes[0] should be the first node being chosen when inserting into the actual linked list
    list->free = 0;
    list->length = 0;
    list->listSize = INITIAL_CAPACITY;

    clear(list);
    return list;
}

// Destroy
void destroy(StaticLinkedList *list) {
    free(list);
}

// Get element by index
int get(StaticLinkedList *list, int index) {
    if (index < 0 || index >= list->length) {
        return -1;
    }
    int current = list->head;
    for (int i = 0; i < index; i++) {
        current = list->nodes[current].next;
    }
    return list->nodes[current].data;
}

// Get element by value
int indexOf(StaticLinkedList *list, int value) {
    int current = list->head;
    int index = 0;
    while (current != NULL_INDEX) {
        if (list->nodes[current].data == value) {
            return index;
        }
        current = list->nodes[current].next;
        index++;
    }
    return -1;
}

// Insert a node to the given index
int insert(StaticLinkedList *list, int index, int value) {
    if (index < 0 || index > list->length || list->free == NULL_INDEX) {
        return -1;
    }
    int newNode = list->free;
    list->free = list->nodes[newNode].next;
    list->nodes[newNode].data = value;
    if (index == 0) {
        list->nodes[newNode].next = list->head;
        list->head = newNode;
    } else {
        // find the actual index in list->nodes corresponding to index of the linked list
        int prev = list->head;
        for (int i = 0; i < index - 1; i++) {
            prev = list->nodes[prev].next;
        }

        list->nodes[newNode].next = list->nodes[prev].next;
        list->nodes[prev].next = newNode;
    }
    list->length++;
    return 0;
}

// Remove a node at the given index
int removeNode(StaticLinkedList *list, int index) {
    if (index < 0 || index >= list->length) {
        return -1;
    }
    int toRemove;
    if (index == 0) {
        toRemove = list->head;
        list->head = list->nodes[toRemove].next;
    } else {
        // find the actual index in list->nodes corresponding to index of the linked list
        int prev = list->head;
        for (int i = 0; i < index - 1; i++) {
            prev = list->nodes[prev].next;
        }

        toRemove = list->nodes[prev].next;
        list->nodes[prev].next = list->nodes[toRemove].next;
    }

    // mark the removed node to be in the free linked list
    list->nodes[toRemove].next = list->free;
    list->free = toRemove;
    list->length--;
    return 0;
}

int main() {
    StaticLinkedList *list = init();

    insert(list, 0, 10);
    insert(list, 1, 20);
    insert(list, 2, 30);

    printf("Element at index 1: %d\n", get(list, 1));
    printf("Index of value 20: %d\n", indexOf(list, 20));
    printf("Length: %d\n", length(list));
    printf("Capacity: %d\n", size(list));
    printf("Is empty: %d\n", empty(list));

    removeNode(list, 1);
    printf("Element at index 1 after removal: %d\n", get(list, 1));

    clear(list);
    printf("Is empty after clear: %d\n", empty(list));

    destroy(list);

    return 0;
}
