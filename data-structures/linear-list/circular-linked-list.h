//
// Created by Hoarfroster on 21/7/2024.
//

#ifndef C_ALGORITHM_CIRCULAR_LINKED_LIST_H
#define C_ALGORITHM_CIRCULAR_LINKED_LIST_H

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct CircularLinkedList {
    Node *tail;
    int length;
} CircularLinkedList;

// Clear the list
void clear(CircularLinkedList *list);

// Whether the list is empty
int empty(CircularLinkedList *list);

// Length of the list
int length(CircularLinkedList *list);

// Print the list
void printList(CircularLinkedList *list);

// Initialization
CircularLinkedList *init();

// Destroy
void destroy(CircularLinkedList *list);

// Get element by index
int get(CircularLinkedList *list, int index);

// Get element by value
int indexOf(CircularLinkedList *list, int value);

// Insert a node to the given index
void insert(CircularLinkedList *list, int index, int value);

// Remove a node at the given index
void removeNode(CircularLinkedList *list, int index);

#endif //C_ALGORITHM_CIRCULAR_LINKED_LIST_H
