//
// Created by Hoarfroster on 20/7/2024.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head;
    int length;
} LinkedList;

// Initialization
LinkedList *init() {
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList)); // allocate memory for the list

    // point the head of the list to a NULL and set its length to 0 - like a empty linked list should be
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
int get(LinkedList *list, int pos, int *element) {
    if (pos < 0 || pos >= list->length) {
        return 0;
    }
    Node *current = list->head;
    for (int i = 0; i < pos; i++) {
        current = current->next;
    }
    *element = current->data;
    return 1;
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
int insert(LinkedList *list, int index, int value) {
    if (index < 0 || index > list->length) {
        return 0;
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
    return 1;
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
        previous->next = current->next;
        free(current);
    }
    list->length--;
}

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

int main() {
    LinkedList *list = init();

    insert(list, 0, 10);
    insert(list, 1, 20);
    insert(list, 2, 30);
    printList(list);

    int value;
    if (get(list, 1, &value)) {
        printf("The element at position 1 is %d\n", value);
    } else {
        printf("Failed to get element at position 1\n");
    }
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