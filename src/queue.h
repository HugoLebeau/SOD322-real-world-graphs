#ifndef QUEUE_H
#define QUEUE_H

typedef struct element element;
struct element {
    unsigned long value;
    element* next;
};

typedef struct {
    element* first;
} fifo;

fifo* queue_alloc();
element* get_last(fifo* queue);
void enqueue(int value, fifo* queue);
unsigned long dequeue(fifo* queue);
void free_queue(fifo* queue);

#endif
