//
// Created by Hoarfroster on 21/7/2024.
//

#ifndef C_ALGORITHM_SINGLE_LINKED_LIST_H
#define C_ALGORITHM_SINGLE_LINKED_LIST_H

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head;
    int length;
} LinkedList;

// Clear the list
void clear(LinkedList *list);

// Whether the list is empty
int empty(LinkedList *list);

// Length of the list
int length(LinkedList *list);

// Print the list
void printList(LinkedList *list);

// Initialization
LinkedList *init();

// Destroy
void destroy(LinkedList *list);

// Get element by *index*
Node* get(LinkedList *list, int index);

// Get element by *value*
int indexOf(LinkedList *list, int value);

// Insert an element by index
void insert(LinkedList *list, int index, int value);

// Remove an element by index
void removeNode(LinkedList *list, int index);

#endif //C_ALGORITHM_SINGLE_LINKED_LIST_H
