#include <stdlib.h>
#include <stdio.h>
#include "min_heap.h"

min_heap* alloc_min_heap(unsigned long capacity) {
    min_heap *mh = malloc(sizeof(min_heap));
    mh->arr = malloc(capacity*sizeof(node));
    mh->capacity = capacity;
    mh->size = 0;
    return mh;
}

// Swap two elements of an array
void swap_node(node* array, unsigned long i, unsigned long j) {
    node buffer = array[i];
    array[i] = array[j];
    array[j] = buffer;
}

// Insert node (n, d) into a min heap
void insert_node(min_heap* mh, unsigned long n, unsigned long d) {
    if (mh->size >= mh->capacity) {
        printf("Min heap reached maximum capacity. Cannot insert key.\n");
        return;
    }
    int i = mh->size;
    mh->size++;
    mh->arr[i].n = n;
    mh->arr[i].d = d;
    int parent = (i-1)/2;
    while (i > 0 && mh->arr[parent].d > mh->arr[i].d) {
        swap_node(mh->arr, i, parent);
         i = parent;
         parent = (i-1)/2;
    }
}

// Decrease by 1 the degree of node i in the min heap
void decrease_degree(min_heap* mh, unsigned long i) {
    mh->arr[i].d -= 1;
    unsigned long parent = (i-1)/2;
    while (i != 0 && mh->arr[parent].d > mh->arr[i].d) {
        swap_node(mh->arr, i, parent);
        i = parent;
        parent = (i-1)/2;
    }
}

// A recursive function to heapify a subtree with the root at given index 
// This function assumes that the subtrees are already heapified
void make_min_heap(min_heap* mh, unsigned long i) {
    unsigned long left = 2*i+1, right = 2*i+2, smallest = i;
    if (left < mh->size && mh->arr[left].d < mh->arr[smallest].d) {
        smallest = left;
    }
    if (right < mh->size && mh->arr[right].d < mh->arr[smallest].d) {
        smallest = right;
    }
    if (smallest != i) {
        swap_node(mh->arr, i, smallest);
        make_min_heap(mh, smallest);
    }
}

// Extract the min of a min heap
node extract_min(min_heap* mh) {
    if (mh->size <= 0) {
        printf("Error: empty min heap.\n");
        node null_node;
        null_node.n = 0;
        null_node.d = 0;
        return null_node;
    }
    if (mh->size == 1) {
        mh->size = 0;
        return mh->arr[0];
    }
    node root = mh->arr[0];
    mh->arr[0] = mh->arr[mh->size-1];
    mh->size--;
    make_min_heap(mh, 0);
    return root;
}

void free_min_heap(min_heap *mh) {
    free(mh->arr);
    free(mh);
}
