//
// Created by Hoarfroster on 05/8/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "sequential-queue.h"

// Clear the queue
void clear(SequentialQueue *queue) {
    queue->front = -1;
    queue->rear = 0;
}

// Whether the queue is empty
int empty(SequentialQueue *queue) {
    return queue->front == queue->rear - 1;
}

// Length of the queue
int length(SequentialQueue *queue) {
    return queue->front - queue->rear + 1;
}

// Capacity (size) of the queue
int size(SequentialQueue *queue) {
    return queue->queueSize;
}

// Initialization
SequentialQueue *init() {
    SequentialQueue *queue = (SequentialQueue *) malloc(sizeof(SequentialQueue));
    if (queue == NULL) {
        printf("Failed to allocate memory\n");
        exit(1);
    }

    queue->data = (int *) malloc(INITIAL_CAPACITY * sizeof(int));
    if (queue->data == NULL) {
        printf("Failed to allocate memory\n");
        exit(1);
    }

    clear(queue);
    queue->queueSize = INITIAL_CAPACITY;
    return queue;
}

// Destroy
void destroy(SequentialQueue *queue) {
    free(queue->data);
    queue->data = NULL;
    clear(queue);
    queue->queueSize = 0;
}

// Push an element to the front
int enqueue(SequentialQueue *queue, int value) {
    if (queue->front == queue->queueSize - 1) {
        int newCapacity = queue->queueSize * 2;
        int *newData = (int *) realloc(queue->data, newCapacity * sizeof(int));
        if (newData == NULL) return 0; // failed to allocate memory - queue overflow
        queue->data = newData;
        queue->queueSize = newCapacity;
    }
    queue->data[++queue->front] = value;
    return 1;
}

// Pop the rear element
int dequeue(SequentialQueue *queue, int *value) {
    if (queue->rear == -1) return 0;
    *value = queue->data[queue->rear++];
    return 1;
}
