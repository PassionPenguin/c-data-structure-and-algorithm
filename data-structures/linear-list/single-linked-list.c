//
// Created by Hoarfroster on 20/7/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "single-linked-list.h"

// Clear the list
void clear(LinkedList *list) {
    Node *current = list->head;
    Node *next;
    while (current != NULL) {
        next = current->next;
        free(current); // free the memory of all nodes
        current = next;
    }
    list->head = NULL;
    list->length = 0;
}

// Whether the list is empty
int empty(LinkedList *list) {
    return list->length == 0;
}

// Length of the list
int length(LinkedList *list) {
    return list->length;
}

// Print the list
void printList(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Initialization
LinkedList *init() {
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList)); // allocate memory for the list
    if(list == NULL) {
        printf("Failed to allocate memory for the list\n");
        exit(1);
    }

    // point the head of the list to a NULL and set its length to 0 - like an empty linked list should be
    list->head = NULL;
    list->length = 0;
    return list;
}

// Destroy
void destroy(LinkedList *list) {
    Node *current = list->head;
    Node *next;

    // free the memory of all nodes
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(list); // free the memory of the list
}

// Get element by index
Node* get(LinkedList *list, int index) {
    if (index < 0 || index >= list->length) {
        return NULL;
    }
    Node *current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

// Get element by value
int indexOf(LinkedList *list, int value) {
    Node *current = list->head;
    int index = 0;
    while (current != NULL) {
        if (current->data == value) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1; // not found
}

// Insert a node to the given index
void insert(LinkedList *list, int index, int value) {
    if (index < 0 || index > list->length) {
        return;
    }
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->data = value;
    if (index == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        Node *current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    list->length++;
}

// Remove a node at the given index
void removeNode(LinkedList *list, int index) {
    if (index < 0 || index >= list->length) {
        printf("Index out of bounds\n");
        return;
    }
    Node *current = list->head;
    if (index == 0) {
        list->head = current->next;
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
            free(current);
        }
    }
    list->length--;
}
