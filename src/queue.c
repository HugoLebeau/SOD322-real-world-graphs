#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

fifo* queue_alloc() {
    fifo *queue = malloc(sizeof(fifo));
    queue->first = NULL;
    return queue;
}

element* get_last(fifo* queue) {
    element *curr = queue->first;
    if (!curr) return NULL;
    while (curr->next) {
        curr = curr->next;
    }
    return curr;
}

void enqueue(int value, fifo* queue) {
    element *last = get_last(queue);
    if (last) {
        last->next = malloc(sizeof(element*));
        last->next->value = value;
        last->next->next = NULL;
    }
    else {
        queue->first = malloc(sizeof(element*));
        queue->first->value = value;
        queue->first->next = NULL;
    }
}

unsigned long dequeue(fifo* queue) {
    element *first = queue->first;
    if (!first) {
        printf("Error: trying to dequeue from an empty queue.\n");
        return 0;
    }
    unsigned long value = first->value;
    queue->first = first->next;
    free(first);
    return value;
}

void free_queue(fifo* queue) {
    element *curr = queue->first;
    element *buffer;
    while (curr) {
        buffer = curr;
        curr = curr->next;
        free(buffer);
    }
    free(queue);
}
