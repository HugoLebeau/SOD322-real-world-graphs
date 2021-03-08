#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <stdbool.h>

typedef struct {
    unsigned long n; //label of the node
    unsigned long d; //degree of the node
} node;

typedef struct {
    node *arr; //elements of the min heap
    unsigned long *where; //where[n] is the position in the min heap of the node with label n
    bool *in; //in[n] is true iff node with label n is in the min heap
    unsigned long capacity; //maximum size of the min heap
    unsigned long size; //number of elements in the min heap
} min_heap;

min_heap* alloc_min_heap(unsigned long capacity);
void insert_node(min_heap* mh, unsigned long n, unsigned long d);
void decrease_degree(min_heap* mh, unsigned long i);
node extract_min(min_heap* mh);
void free_min_heap(min_heap *mh);

#endif
