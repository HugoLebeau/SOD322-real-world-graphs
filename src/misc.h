#ifndef MISC_H
#define MISC_H

unsigned long max(unsigned long a, unsigned long b);
void quicksort(unsigned long* array, unsigned long* idx, unsigned long first, unsigned long last);
void intersection(unsigned long* sorted_a, unsigned long size_a, unsigned long* sorted_b, unsigned long size_b, unsigned long* inter, unsigned long* size_inter);

typedef struct {
    unsigned long n_elems; //number of elements
    unsigned long capacity; //maximum number of elements
    unsigned long n, p; //dimensions
    double *val; //value of each element
    unsigned long *row; //row of each element
    unsigned long *col; //column of each element
} sparse_matrix;

sparse_matrix* alloc_sparse_matrix(unsigned long capacity, unsigned long n, unsigned long p);
void add_elem(sparse_matrix* mat, double elem, unsigned long i, unsigned long j);
void matvecprod(sparse_matrix* mat, double* vec, double* res);
void free_sparse_matrix(sparse_matrix* mat);

#endif
