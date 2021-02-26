#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

#define NLINKS 100000000 //maximum number of edges for memory allocation, will increase if needed

typedef struct {
	unsigned long s;
	unsigned long t;
} edge;

//edge list structure
typedef struct {
	unsigned long n; //number of nodes
	unsigned long e; //number of edges
	edge *edges; //list of edges
} edgelist;

//adjacency list structure
typedef struct {
    unsigned long n; //number of nodes
	unsigned long e; //number of edges
	edge *edges; //list of edges
	unsigned long *cd; //cumulative degree cd[0]=0 length=n+1
	unsigned long *adj; //concatenated list of neighbors of all nodes
} adjlist;

//adjacency matrix structure
typedef struct {
	unsigned long n; //number of nodes
	unsigned long e; //number of edges
	edge *edges; //list of edges
	bool *mat; //adjacency matrix
} adjmatrix;

unsigned long max3(unsigned long a, unsigned long b, unsigned long c);

edgelist* read_edgelist(char* input);
void free_edgelist(edgelist* g);

adjlist* read_adjlist(char* input);
void mkadjlist(adjlist* g);
void sort_neighbors(adjlist* g);
void free_adjlist(adjlist* g);

adjmatrix* read_adjmatrix(char* input);
void mkmatrix(adjmatrix* g);
void free_adjmatrix(adjmatrix* g);

#endif
