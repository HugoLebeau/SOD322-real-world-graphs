#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef struct element element;
struct element {
    unsigned long value;
    element *next;
};

typedef struct {
    element *first;
    element *last;
    unsigned long n_elements;
} fifo;

fifo* queue_alloc();
bool is_empty(fifo* queue);
void enqueue(unsigned long value, fifo* queue);
unsigned long dequeue(fifo* queue);
void free_queue(fifo* queue);

#endif
