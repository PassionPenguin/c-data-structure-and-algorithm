//
// Created by Hoarfroster on 05/8/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "circular-sequential-queue.h"


// Clear the queue
void clear(CircularSequentialQueue *queue) {
    queue->front = 0;
    queue->rear = 0;
    queue->length = 0;
}

// Whether the queue is empty
int empty(CircularSequentialQueue *queue) {
    return queue->length == 0;
}

// Length of the queue
int length(CircularSequentialQueue *queue) {
    return queue->length;
}

// Capacity of the queue
int size(CircularSequentialQueue *queue) {
    return queue->queueSize;
}

// Initialization
CircularSequentialQueue *init() {
    CircularSequentialQueue *queue = (CircularSequentialQueue *)malloc(sizeof(CircularSequentialQueue));
    queue->data = (int *)malloc(INITIAL_CAPACITY * sizeof(int));
    queue->rear = 0;
    queue->front = 0;
    queue->queueSize = INITIAL_CAPACITY;
    queue->length = 0;
    return queue;
}

// Destroy
void destroy(CircularSequentialQueue *queue) {
    free(queue->data);
    free(queue);
}

// Push an element to the rear
int enqueue(CircularSequentialQueue *queue, int value) {
    if (queue->length == queue->queueSize) {
        // Queue is full, need to expand capacity
        int newSize = queue->queueSize * 2;
        int *newData = (int *)malloc(newSize * sizeof(int));
        if (newData == NULL) {
            return 0; // Memory allocation failed
        }

        // Copy data to new array
        for (int i = 0; i < queue->length; i++) {
            newData[i] = queue->data[(queue->front + i) % queue->queueSize];
        }
        free(queue->data);
        queue->data = newData;
        queue->queueSize = newSize;
        queue->front = 0;
        queue->rear = queue->length;
    }

    queue->data[queue->rear] = value;
    queue->rear = (queue->rear + 1) % queue->queueSize;
    queue->length++;
    return 1;
}

// Pop the front element
int dequeue(CircularSequentialQueue *queue, int *value) {
    if (empty(queue)) {
        return 0; // Queue is empty
    }
    *value = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->queueSize;
    queue->length--;
    return 1;
}
