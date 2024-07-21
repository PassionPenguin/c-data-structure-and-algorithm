//
// Created by Hoarfroster on 21/7/2024.
//

#ifndef C_ALGORITHM_STATIC_LINKED_LIST_H
#define C_ALGORITHM_STATIC_LINKED_LIST_H

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
void clear(StaticLinkedList *list);

// Whether the list is empty
int empty(StaticLinkedList *list);

// Length of the list
int length(StaticLinkedList *list);

// Capacity (size) of the list
int size(StaticLinkedList *list);

// Initialization
StaticLinkedList *init();

// Destroy
void destroy(StaticLinkedList *list);

// Get element by *index*
Node* get(StaticLinkedList *list, int index);

// Get element by *value*
int indexOf(StaticLinkedList *list, int value);

// Insert an element by index
void insert(StaticLinkedList *list, int index, int value);

// Remove an element by index
void removeNode(StaticLinkedList *list, int index);

#endif //C_ALGORITHM_STATIC_LINKED_LIST_H
