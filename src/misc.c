#include <stdlib.h>
#include <stdio.h>
#include "misc.h"

unsigned long max(unsigned long a, unsigned long b) {
    return (a > b ? a : b);
}

// Swap two elements of an array
void swap_lu(unsigned long* array, unsigned long i, unsigned long j) {
    unsigned long buffer = array[i];
    array[i] = array[j];
    array[j] = buffer;
}

// Partition function of the quicksort
unsigned long partition(unsigned long* array, unsigned long* idx, unsigned long first, unsigned long last) {
    unsigned long pivot = array[last];
    unsigned long i = first, j;
    for (j = first; j <= last; j++) {
        if (array[j] < pivot) {
            swap_lu(array, i, j);
            swap_lu(idx, i, j);
            i++;
        }
    }
    swap_lu(array, i, last);
    swap_lu(idx, i, last);
    return i;
}

// Quicksort of an array
void quicksort(unsigned long* array, unsigned long* idx, unsigned long first, unsigned long last) {
    if (first < last) {
        unsigned long p = partition(array, idx, first, last);
        if (p >= 1) quicksort(array, idx, first, p-1);
        quicksort(array, idx, p+1, last);
    }
}

// Intersection of two SORTED arrays
// inter array is supposed to have enough memory allocated
void intersection(unsigned long* sorted_a, unsigned long size_a, unsigned long* sorted_b, unsigned long size_b, unsigned long* inter, unsigned long* size_inter) {
    unsigned long i = 0, j = 0, k = 0;
    while (i < size_a && j < size_b) {
        if (sorted_a[i] < sorted_b[j]) i++;
        else if (sorted_a[i] > sorted_b[j]) j++;
        else {
            inter[k] = sorted_a[i];
            i++; j++; k++;
        }
    }
    *size_inter = k;
}

sparse_matrix* alloc_sparse_matrix(unsigned long capacity, unsigned long n, unsigned long p) {
    sparse_matrix* mat = malloc(sizeof(sparse_matrix));
    mat->n_elems = 0;
    mat->capacity = capacity;
    mat->n = n;
    mat->p = p;
    mat->val = malloc(capacity*sizeof(double));
    mat->pos = malloc(capacity*sizeof(unsigned long));
    return mat;
}

void add_elem(sparse_matrix* mat, double elem, unsigned long i, unsigned long j) {
    if (mat->n_elems >= mat->capacity) {
        printf("Sparse matrix reached maximum capacity. Cannot add element.\n");
        return;
    }
    mat->val[mat->n_elems] = elem;
    mat->pos[mat->n_elems] = mat->p*i+j;
    mat->n_elems++;
}

// Matrix vector product with a sparse matrix
void matvecprod(sparse_matrix* mat, double* vec, double* res) {
    unsigned long i, j, k;
    for (i = 0; i < mat->p; i++) res[i] = 0.;
    for (k = 0; k < mat->n_elems; k++) {
        i = mat->pos[k]/mat->p;
        j = mat->pos[k]%mat->p;
        res[i] += mat->val[k]*vec[j];
    }
}

void free_sparse_matrix(sparse_matrix* mat) {
    free(mat->val);
    free(mat->pos);
    free(mat);
}
