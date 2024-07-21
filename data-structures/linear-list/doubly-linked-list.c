//
// Created by Hoarfroster on 20/7/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "doubly-linked-list.h"

// Clear the list
void clear(DoublyLinkedList* list) {
    Node* current = list->head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
}

// Whether the list is empty
int empty(DoublyLinkedList* list) {
    return list->length == 0;
}

// Length of the list
int length(DoublyLinkedList* list) {
    return list->length;
}

// Print the list
void printList(DoublyLinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Initialization
DoublyLinkedList* init() {
    DoublyLinkedList* list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    if(list == NULL) {
        printf("Failed to allocate memory\n");
        exit(1);
    }

    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    return list;
}

// Destroy the list
void destroy(DoublyLinkedList* list) {
    Node* current = list->head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

// Get element by index
Node* get(DoublyLinkedList* list, int index) {
    if (index < 0 || index >= list->length) {
        return NULL;
    }
    Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

// Get element by value
int indexOf(DoublyLinkedList* list, int value) {
    Node* current = list->head;
    int index = 0;
    while (current != NULL) {
        if (current->data == value) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

// Insert a node to the given index
void insert(DoublyLinkedList* list, int index, int value) {
    if (index < 0 || index > list->length) {
        return;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    if (index == 0) {
        newNode->next = list->head;
        newNode->prev = NULL;
        if (list->head != NULL) {
            list->head->prev = newNode;
        }
        list->head = newNode;
        if (list->tail == NULL) {
            list->tail = newNode;
        }
    } else {
        Node* prevNode = get(list, index - 1);
        newNode->next = prevNode->next;
        newNode->prev = prevNode;
        if (prevNode->next != NULL) {
            prevNode->next->prev = newNode;
        }
        prevNode->next = newNode;
        if (newNode->next == NULL) {
            list->tail = newNode;
        }
    }
    list->length++;
}

// Remove a node at the given index
void removeNode(DoublyLinkedList* list, int index) {
    if (index < 0 || index >= list->length) {
        return;
    }
    Node* current = get(list, index);
    if(current != NULL) {
        if (current->prev != NULL) {
            current->prev->next = current->next;
        } else {
            list->head = current->next;
        }
        if (current->next != NULL) {
            current->next->prev = current->prev;
        } else {
            list->tail = current->prev;
        }
        free(current);
    }
    list->length--;
}
