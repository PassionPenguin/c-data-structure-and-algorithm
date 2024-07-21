//
// Created by Hoarfroster on 19/7/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "sequential-list.h"

// Clear the list
void clear(SequentialList *list) {
    list->length = 0;
}

// Whether the list is empty
int empty(SequentialList *list) {
    return list->length == 0;
}

// Length of the list
int length(SequentialList *list) {
    return list->length;
}

// Capacity (size) of the list
int size(SequentialList *list) {
    return list->capacity;
}

// Initialization
SequentialList *init() {
    SequentialList *list = (SequentialList *) malloc(sizeof(SequentialList)); // allocate memory for the list
    if(list == NULL) {
        printf("Failed to allocate memory for the list\n");
        exit(1);
    }

    list->data = (int *) malloc(sizeof(int) * INITIAL_CAPACITY); // allocate memory for the data contained in the list
    list->length = 0;
    list->capacity = INITIAL_CAPACITY;
    return list;
}

// Destroy
void destroy(SequentialList *list) {
    free(list->data); // free the memory allocated for the data
    free(list); // free the memory allocated for the list
}

// Get element by *index*
int* get(SequentialList *list, int index) {
    if (index < 0 || index >= list->length) {
        return NULL;
    }
    return &list->data[index];
}

// Get element by *value*
int indexOf(SequentialList *list, int value) {
    for (int i = 0; i < list->length; i++) {
        if (list->data[i] == value) {
            return i;
        }
    }
    return -1; // not found
}

// Insert an element by index
int insert(SequentialList *list, int index, int value) {
    if (index < 0 || index > list->length) {
        return 0;
    }

    // check if the list is full, and increase the capacity if so
    if (list->length == list->capacity) {
        // increase the capacity by twice
        list->capacity *= 2;
        int* data = (int *) realloc(list->data, sizeof(int) * list->capacity);
        if(!data) return 0; // failed to re-allocate memory to increase the capacity
        list->data = data;
    }

    // moving elements to the right
    for (int i = list->length; i > index; i--) {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = value;
    list->length++;
    return 1;
}

// Remove an element by index
void removeNode(SequentialList *list, int index) {
    if (index < 0 || index >= list->length) {
        return;
    }
    for (int i = index; i < list->length - 1; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->length--;
}
