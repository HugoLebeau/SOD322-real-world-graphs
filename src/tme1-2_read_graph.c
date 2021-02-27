#include <stdlib.h>
#include <stdio.h>
#include <time.h> //to estimate the running time
#include "graph.h"

int main(int argc, char** argv) {
	edgelist *g1;
	adjlist *g2;
	adjmatrix *g3;
	time_t t1, t2;

	printf("File: \"%s\".\n", argv[1]);
	
	printf("Loading graph as an edge list...\n");
	t1 = time(NULL);
	g1 = read_edgelist(argv[1]);
	t2 = time(NULL);
	printf("Done. Time: %lus.\nNumber of nodes: %lu.\nNumber of edges: %lu.\n", (unsigned long) difftime(t2, t1), g1->n, g1->e);
	free_edgelist(g1);
	
	printf("Loading graph as an adjacency list...\n");
	t1 = time(NULL);
	g2 = read_adjlist(argv[1]);
	mkadjlist(g2);
	t2 = time(NULL);
	printf("Done. Time: %lus.\nNumber of nodes: %lu.\nNumber of edges: %lu.\n", (unsigned long) difftime(t2, t1), g2->n, g2->e);
	free_adjlist(g2);
	
	printf("Loading graph as an adjacency matrix...\n");
	t1 = time(NULL);
	g3 = read_adjmatrix(argv[1]);
	mkmatrix(g3); //this will surely crash unless the graph is small
	t2 = time(NULL);
	printf("Done. Time: %lus.\nNumber of nodes: %lu.\nNumber of edges: %lu.\n", (unsigned long) difftime(t2, t1), g3->n, g3->e);
	free_adjmatrix(g3);

	return 0;
}
