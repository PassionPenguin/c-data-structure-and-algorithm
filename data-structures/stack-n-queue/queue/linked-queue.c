//
// Created by Hoarfroster on 20/7/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "linked-queue.h"

// Clear the queue
void clear(LinkedQueue *queue) {
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
int empty(LinkedQueue *queue) {
    return queue->front == NULL;
}

// Length of the queue
int length(LinkedQueue *queue) {
    return queue->length;
}

// Initialization
LinkedQueue *init() {
    LinkedQueue *queue = (LinkedQueue *) malloc(sizeof(LinkedQueue));
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
void destroy(LinkedQueue *queue) {
    clear(queue);
    free(queue);
}

// Push an element to the front
int enqueue(LinkedQueue *queue, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        return 0; // failed to allocate memory - i.e. queue overflow
    }
    newNode->data = value;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }

    queue->length++;

    return 1;
}

// Pop the rear element
int dequeue(LinkedQueue *queue, int *value) {
    if (queue->front == NULL) {
        return 0; // queue already empty
    }
    
    Node *temp = queue->front;
    *value = temp->data;

    queue->front = queue->front->next;
    queue->length--;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    return 1;
}
