#ifndef GRAPH_H
#define GRAPH_H

#include "misc.h"
#include "min_heap.h"

#define NLINKS 100000000 //maximum number of edges for memory allocation, will increase if needed

typedef struct {
	unsigned long s;
	unsigned long t;
} edge;

// Edge list structure
typedef struct {
	unsigned long n; //number of nodes
	unsigned long e; //number of edges
	edge *edges; //list of edges
} edgelist;

// Adjacency list structure
typedef struct {
    unsigned long n; //number of nodes
	unsigned long e; //number of edges
	edge *edges; //list of edges
	unsigned long *cd; //cumulative degree cd[0]=0 length=n+1
	unsigned long *adj; //concatenated list of neighbors of all nodes
	min_heap *mh; //min heap of the nodes sorted by their degree (filled only if needed)
} adjlist;

// Adjacency matrix structure
typedef struct {
	unsigned long n; //number of nodes
	unsigned long e; //number of edges
	edge *edges; //list of edges
	bool *mat; //adjacency matrix
} adjmatrix;

// Sparse transition matrix structure for ORIENTED graphs
typedef struct {
	unsigned long n; //number of nodes
	unsigned long e; //number of edges
	edge *edges; //list of edges
	sparse_matrix *mat; //transition matrix
} sptmatrix;

edgelist* read_edgelist(char* input);
void free_edgelist(edgelist* g);

adjlist* read_adjlist(char* input);
void mkadjlist(adjlist* g);
void sort_neighbors(adjlist* g);
void sort_nodes(adjlist *g);
void free_adjlist(adjlist* g);

adjmatrix* read_adjmatrix(char* input);
void mkmatrix(adjmatrix* g);
void free_adjmatrix(adjmatrix* g);

sptmatrix* read_sptmatrix(char* input);
void mksptmatrix(sptmatrix* g);
void free_sptmatrix(sptmatrix* g);

#endif
