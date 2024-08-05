//
// Created by Hoarfroster on 06/8/2024.
//

#include <stdio.h>
#include "linked-queue.h"

int main() {
    LinkedQueue *queue = init();
    int value;

    enqueue(queue, 1);
    printf("Enqueued %d to front\n", 1);
    dequeue(queue, &value);
    printf("Dequeued %d from rear\n", value);
    enqueue(queue, 2);
    printf("Enqueued %d to front\n", 2);
    enqueue(queue, 3);
    printf("Enqueued %d to front\n", 3);

    printf("Length of the queue: %d\n", length(queue));

    dequeue(queue, &value);
    printf("Dequeued %d from rear\n", value);
    dequeue(queue, &value);
    printf("Dequeued %d from rear\n", value);

    clear(queue);
    destroy(queue);

    return 0;
}