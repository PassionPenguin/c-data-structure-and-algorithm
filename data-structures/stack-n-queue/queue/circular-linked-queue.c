//
// Created by Hoarfroster on 06/8/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "circular-linked-queue.h"

// Clear the queue
void clear(CircularLinkedQueue *queue) {
    Node *current = queue->rear;
    Node *nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    queue->front = NULL;
    queue->rear = NULL;
    queue->length = 0;
}

// Whether the queue is empty
int empty(CircularLinkedQueue *queue) {
    return queue->front == NULL;
}

// Length of the queue
int length(CircularLinkedQueue *queue) {
    return queue->length;
}

// Initialization
CircularLinkedQueue *init() {
    CircularLinkedQueue *queue = (CircularLinkedQueue *) malloc(sizeof(CircularLinkedQueue));
    if(queue == NULL) {
        printf("Failed to allocate memory\n");
        exit(1);
    }

    queue->front = NULL;
    queue->rear = NULL;
    queue->length = 0;
    return queue;
}

// Destroy
void destroy(CircularLinkedQueue *queue) {
    clear(queue);
    free(queue);
}

// Push an element to the rear
int enqueue(CircularLinkedQueue *queue, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        return 0; // failed to allocate memory - i.e. queue overflow
    }
    newNode->data = value;
    if (empty(queue)) {
        newNode->next = newNode; // link circularly
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        // Insert new node at the rear
        newNode->next = queue->rear->next;
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->length++;

    return 1;
}

// Pop the front element
int dequeue(CircularLinkedQueue *queue, int *value) {
    if (queue->front == NULL) {
        return 0; // queue already empty
    }
    
    Node *temp = queue->front;
    *value = temp->data;
    if (queue->length == 1) {
        // if only containing one element
        queue->front = NULL;
        queue->rear = NULL;
    } else {
        // remove the front element
        queue->front = temp->next;
        queue->rear->next = queue->front;
    }
    free(temp);
    queue->length--;

    return 1;
}
