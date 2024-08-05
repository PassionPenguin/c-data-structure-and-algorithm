//
// Created by Hoarfroster on 21/7/2024.
//

#ifndef C_ALGORITHM_LINKED_QUEUE_H
#define C_ALGORITHM_LINKED_QUEUE_H

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct LinkedQueue {
    Node *front;
    Node *rear;
    int length;
} LinkedQueue;

// Clear the queue
void clear(LinkedQueue *queue);

// Whether the queue is empty
int empty(LinkedQueue *queue);

// Length of the queue
int length(LinkedQueue *queue);

// Initialization
LinkedQueue *init();

// Destroy
void destroy(LinkedQueue *queue);

// Push an element to the front
int enqueue(LinkedQueue *queue, int value);

// Pop the rear element
int dequeue(LinkedQueue *queue, int *value);

#endif //C_ALGORITHM_LINKED_QUEUE_H
