#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "misc.h"

// Compute the maximum of three unsigned long
unsigned long max3(unsigned long a, unsigned long b, unsigned long c) {
	a = (a > b) ? a : b;
	return (a > c) ? a : c;
}

// Read an edge list from file
edgelist* read_edgelist(char* input) {
	unsigned long e1 = NLINKS;
	FILE *file = fopen(input, "r");

	edgelist *g = malloc(sizeof(edgelist));
	g->n = 0;
	g->e = 0;
	g->edges = malloc(e1*sizeof(edge)); //allocate some RAM to store edges
    
	while (fscanf(file, "%lu %lu", &(g->edges[g->e].s), &(g->edges[g->e].t)) == 2) {
		g->n = max3(g->n, g->edges[g->e].s, g->edges[g->e].t);
		if (++(g->e) == e1) { //increase allocated RAM if needed
			e1 += NLINKS;
			g->edges = realloc(g->edges, e1*sizeof(edge));
		}
	}
	fclose(file);

	g->n++;
	g->edges = realloc(g->edges, g->e*sizeof(edge));

	return g;
}

void free_edgelist(edgelist* g) {
	free(g->edges);
	free(g);
}

// Read an edge list from file
adjlist* read_adjlist(char* input) {
	unsigned long e1 = NLINKS;
	FILE *file = fopen(input,"r");

	adjlist *g = malloc(sizeof(adjlist));
	g->n = 0;
	g->e = 0;
	g->edges = malloc(e1*sizeof(edge)); //allocate some RAM to store edges

	while (fscanf(file, "%lu %lu", &(g->edges[g->e].s), &(g->edges[g->e].t)) == 2) {
		g->n = max3(g->n, g->edges[g->e].s, g->edges[g->e].t);
		if (++(g->e) == e1) { //increase allocated RAM if needed
			e1 += NLINKS;
			g->edges = realloc(g->edges, e1*sizeof(edge));
		}
	}
	fclose(file);

	g->n++;
	g->edges = realloc(g->edges, g->e*sizeof(edge));

	return g;
}

// Build an adjacency list
void mkadjlist(adjlist* g) {
	unsigned long i, u, v;
	unsigned long *d = calloc(g->n, sizeof(unsigned long));

	for (i = 0; i < g->e; i++) {
		d[g->edges[i].s]++;
		d[g->edges[i].t]++;
	}

	g->cd = malloc((g->n+1)*sizeof(unsigned long));
	g->cd[0] = 0;
	for (i = 1; i < g->n+1; i++) {
		g->cd[i] = g->cd[i-1]+d[i-1];
		d[i-1] = 0;
	}

	g->adj = malloc(2*g->e*sizeof(unsigned long));
	for (i = 0; i < g->e; i++) {
		u = g->edges[i].s;
		v = g->edges[i].t;
		g->adj[g->cd[u]+d[u]++] = v;
		g->adj[g->cd[v]+d[v]++] = u;
	}

	free(d);
}

void sort_neighbors(adjlist* g) {
	unsigned long i;
	for (i = 0; i < g->n; i++) {
		if (g->cd[i+1] > g->cd[i]) quicksort(g->adj, g->cd[i], g->cd[i+1]-1);
	}
}

void free_adjlist(adjlist* g) {
	free(g->edges);
	free(g->cd);
	free(g->adj);
	free(g);
}

// Read an edgelist from file
adjmatrix* read_adjmatrix(char* input) {
	unsigned long e1 = NLINKS;
	FILE *file = fopen(input,"r");

	adjmatrix *g = malloc(sizeof(adjmatrix));
	g->n = 0;
	g->e = 0;
	g->edges = malloc(e1*sizeof(edge)); //allocate some RAM to store edges

	while (fscanf(file, "%lu %lu", &(g->edges[g->e].s), &(g->edges[g->e].t)) == 2) {
		g->n = max3(g->n, g->edges[g->e].s, g->edges[g->e].t);
		if (++(g->e) == e1) { //increase allocated RAM if needed
			e1 += NLINKS;
			g->edges = realloc(g->edges, e1*sizeof(edge));
		}
	}
	fclose(file);

	g->n++;
	g->edges = realloc(g->edges, g->e*sizeof(edge));

	return g;
}

// Build an adjacency matrix
void mkmatrix(adjmatrix* g) {
	unsigned long i, u, v;
	g->mat = calloc(g->n*g->n, sizeof(bool));
	for (i = 0; i < g->e; i++) {
		u = g->edges[i].s;
		v = g->edges[i].t;
		g->mat[u+g->n*v] = 1;
		g->mat[v+g->n*u] = 1;
	}
}

void free_adjmatrix(adjmatrix* g) {
	free(g->edges);
	free(g->mat);
	free(g);
}
