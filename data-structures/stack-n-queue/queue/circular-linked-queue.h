//
// Created by Hoarfroster on 06/8/2024.
//

#ifndef C_ALGORITHM_CIRCULAR_LINKED_QUEUE_H
#define C_ALGORITHM_CIRCULAR_LINKED_QUEUE_H

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct CircularLinkedQueue {
    Node *front;
    Node *rear;
    int length;
} CircularLinkedQueue;

// Clear the queue
void clear(CircularLinkedQueue *queue);

// Whether the queue is empty
int empty(CircularLinkedQueue *queue);

// Length of the queue
int length(CircularLinkedQueue *queue);

// Initialization
CircularLinkedQueue *init();

// Destroy
void destroy(CircularLinkedQueue *queue);

// Push an element to the rear
int enqueue(CircularLinkedQueue *queue, int value);

// Pop the front element
int dequeue(CircularLinkedQueue *queue, int *value);

#endif //C_ALGORITHM_CIRCULAR_LINKED_QUEUE_H
