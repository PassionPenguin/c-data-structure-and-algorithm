//
// Created by Hoarfroster on 20/7/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "circular-linked-list.h"

// Clear the list
void clear(CircularLinkedList *list) {
    list->tail = NULL;
    list->length = 0;
}

// Whether the list is empty
int empty(CircularLinkedList *list) {
    return list->length == 0;
}

// Length of the list
int length(CircularLinkedList *list) {
    return list->length;
}

// Print the list
void printList(CircularLinkedList *list) {
    if (list->tail == NULL) {
        printf("NULL\n");
        return;
    }

    Node *current = list->tail->next;
    do {
        printf("%d -> ", current->data);
        current = current->next;
    } while (current != list->tail->next);
    printf("(back to head)\n");
}

// Initialization
CircularLinkedList *init() {
    CircularLinkedList *list = (CircularLinkedList *) malloc(sizeof(CircularLinkedList));
    if(list == NULL) {
        printf("Failed to allocate memory for the list\n");
        exit(1);
    }

    clear(list);
    return list;
}

// Destroy
void destroy(CircularLinkedList *list) {
    if (list->tail == NULL) return;
    Node *current = list->tail->next;
    Node *next;
    while (current != list->tail) {
        next = current->next;
        free(current);
        current = next;
    }
    free(list->tail);
    list->tail = NULL;
    list->length = 0;
}

// Get element by index
int get(CircularLinkedList *list, int index) {
    if (index < 0 || index >= list->length) {
        printf("Index out of bounds\n");
        return -1; // or some error value
    }
    Node *current = list->tail->next;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

// Get element by value
int indexOf(CircularLinkedList *list, int value) {
    if (list->tail == NULL) return -1;
    Node *current = list->tail->next;
    int index = 0;
    do {
        if (current->data == value) {
            return index;
        }
        current = current->next;
        index++;
    } while (current != list->tail->next);
    return -1;
}

// Insert a node to the given index
void insert(CircularLinkedList *list, int index, int value) {
    if (index < 0 || index > list->length) {
        printf("Index out of bounds\n");
        return;
    }
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    if (list->tail == NULL) {
        newNode->next = newNode;
        list->tail = newNode;
    } else if (index == 0) {
        newNode->next = list->tail->next;
        list->tail->next = newNode;
    } else if (index == list->length) {
        newNode->next = list->tail->next;
        list->tail->next = newNode;
        list->tail = newNode;
    } else {
        Node *current = list->tail->next;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    list->length = list->length + 1;
}

// Remove a node at the given index
void removeNode(CircularLinkedList *list, int index) {
    if (index < 0 || index >= list->length) {
        printf("Index out of bounds\n");
        return;
    }
    if (list->length == 1) {
        free(list->tail);
        list->tail = NULL;
    } else {
        Node *current = list->tail->next;
        if (index == 0) {
            list->tail->next = current->next;
            free(current);
        } else {
            Node *previous = NULL;
            for (int i = 0; i < index; i++) {
                previous = current;
                current = current->next;
            }

            // unable to find the node. however that also means the node is not in the list
            // mostly due to memory corruption
            if(previous == NULL) {
                return;
            } else {
                previous->next = current->next;
                if (current == list->tail) {
                    list->tail = previous;
                }
                free(current);
            }
        }
    }
    list->length--;
}
