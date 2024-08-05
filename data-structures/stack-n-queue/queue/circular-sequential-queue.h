//
// Created by Hoarfroster on 05/8/2024.
//

#ifndef C_ALGORITHM_CIRCULAR_SEQUENTIAL_QUEUE_H
#define C_ALGORITHM_CIRCULAR_SEQUENTIAL_QUEUE_H

#define INITIAL_CAPACITY 10

typedef struct {
    int *data;
    int rear;
    int front;
    int queueSize;
    int length;
} CircularSequentialQueue;

// Clear the queue
void clear(CircularSequentialQueue *queue);

// Whether the queue is empty
int empty(CircularSequentialQueue *queue);

// Length of the queue
int length(CircularSequentialQueue *queue);

// Capacity of the queue
int size(CircularSequentialQueue *queue);

// Initialization
CircularSequentialQueue *init();

// Destroy
void destroy(CircularSequentialQueue *queue);

// Push an element to the rear
int enqueue(CircularSequentialQueue *queue, int value);

// Pop the front element
int dequeue(CircularSequentialQueue *queue, int *value);

#endif //C_ALGORITHM_CIRCULAR_SEQUENTIAL_QUEUE_H
