//
// Created by Hoarfroster on 21/7/2024.
//

#ifndef C_ALGORITHM_DOUBLY_LINKED_LIST_H
#define C_ALGORITHM_DOUBLY_LINKED_LIST_H

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct DoublyLinkedList {
    Node* head;
    Node* tail;
    int length;
} DoublyLinkedList;

// Clear the list
void clear(DoublyLinkedList *list);

// Whether the list is empty
int empty(DoublyLinkedList *list);

// Length of the list
int length(DoublyLinkedList *list);

// Print the list
void printList(DoublyLinkedList *list);

// Initialization
DoublyLinkedList *init();

// Destroy
void destroy(DoublyLinkedList *list);

// Get element by *index*
Node* get(DoublyLinkedList *list, int index);

// Get element by *value*
int indexOf(DoublyLinkedList *list, int value);

// Insert an element by index
void insert(DoublyLinkedList *list, int index, int value);

// Remove an element by index
void removeNode(DoublyLinkedList *list, int index);

#endif //C_ALGORITHM_DOUBLY_LINKED_LIST_H
