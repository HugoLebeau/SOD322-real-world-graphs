#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

fifo* queue_alloc() {
    fifo *queue = malloc(sizeof(fifo));
    queue->first = NULL;
    queue->last = NULL;
    queue->n_elements = 0;
    return queue;
}

bool is_empty(fifo* queue) {
    return (queue->n_elements == 0);
}

// Add an element at the end of a queue
void enqueue(unsigned long value, fifo* queue) {
    if (is_empty(queue)) {
        queue->first = malloc(sizeof(element*));
        queue->first->value = value;
        queue->first->next = NULL;
        queue->last = queue->first;
    }
    else {
        queue->last->next = malloc(sizeof(element*));
        queue->last->next->value = value;
        queue->last->next->next = NULL;
        queue->last = queue->last->next;
    }
    queue->n_elements += 1;
}

// Get and remove the first element of a queue
unsigned long dequeue(fifo* queue) {
    element *first = queue->first;
    if (!first) {
        printf("Error: trying to dequeue from an empty queue.\n");
        return 0;
    }
    unsigned long value = first->value;
    queue->first = first->next;
    free(first);
    queue->n_elements -= 1;
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
