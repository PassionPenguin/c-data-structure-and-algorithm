//
// Created by Hoarfroster on 20/7/2024.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct CircularLinkedList {
    Node *tail;
    int length;
} CircularLinkedList;

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
            previous->next = current->next;
            if (current == list->tail) {
                list->tail = previous;
            }
            free(current);
        }
    }
    list->length--;
}

int main() {
    CircularLinkedList* list = init();

    insert(list, 0, 10);
    insert(list, 1, 20);
    insert(list, 2, 30);
    printList(list);

    printf("Value at index 1: %d\n", get(list, 1));
    printf("Index of value 20: %d\n", indexOf(list, 20));

    removeNode(list, 1);
    printList(list);

    printf("List empty: %d\n", empty(list));
    printf("List length: %d\n", length(list));

    clear(list);
    printList(list);

    destroy(list);

    return 0;
}
