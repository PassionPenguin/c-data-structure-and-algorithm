//
// Created by Hoarfroster on 21/7/2024.
//

#ifndef C_ALGORITHM_SEQUENTIAL_LIST_H
#define C_ALGORITHM_SEQUENTIAL_LIST_H

#define INITIAL_CAPACITY 10

typedef struct {
    int *data;
    int length;
    int capacity;
} SequentialList;

// Clear the list
void clear(SequentialList *list);

// Whether the list is empty
int empty(SequentialList *list);

// Length of the list
int length(SequentialList *list);

// Capacity (size) of the list
int size(SequentialList *list);

// Initialization
SequentialList *init();

// Destroy
void destroy(SequentialList *list);

// Get element by *index*
int* get(SequentialList *list, int index);

// Get element by *value*
int indexOf(SequentialList *list, int value);

// Insert an element by index
int insert(SequentialList *list, int index, int value);

// Remove a node by index
void removeNode(SequentialList *list, int index);

#endif //C_ALGORITHM_SEQUENTIAL_LIST_H
