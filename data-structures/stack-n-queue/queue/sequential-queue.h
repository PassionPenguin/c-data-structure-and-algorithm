//
// Created by Hoarfroster on 05/8/2024.
//

#ifndef C_ALGORITHM_SEQUENTIAL_QUEUE_H
#define C_ALGORITHM_SEQUENTIAL_QUEUE_H

#define INITIAL_CAPACITY 10

typedef struct {
    int *data;
    int rear;
    int front;
    int queueSize;
} SequentialQueue;

// Clear the queue
void clear(SequentialQueue *queue);

// Whether the queue is empty
int empty(SequentialQueue *queue);

// Length of the queue
int length(SequentialQueue *queue);

// Capacity of the queue
int size(SequentialQueue *queue);

// Initialization
SequentialQueue *init();

// Destroy
void destroy(SequentialQueue *queue);

// Push an element to the rear
int enqueue(SequentialQueue *queue, int value);

// Pop the front element
int dequeue(SequentialQueue *queue, int *value);

#endif //C_ALGORITHM_SEQUENTIAL_QUEUE_H
