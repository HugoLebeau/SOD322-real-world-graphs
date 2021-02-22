#include <stdlib.h>
#include <stdio.h>
#include <time.h> //to estimate the running time
#include "graph.h"

int main(int argc, char** argv) {
	edgelist *g1;
	adjlist *g2;
	adjmatrix *g3;
	time_t t1, t2;

	// Read graph as an edge list

	t1 = time(NULL);

	printf("Loading edge list from file %s\n", argv[1]);

	g1 = read_edgelist(argv[1]);

	printf("Number of nodes: %lu\n", g1->n);
	printf("Number of edges: %lu\n", g1->e);

	free_edgelist(g1);

	t2 = time(NULL);

	printf("- Overall time = %llds\n", (t2-t1)%60);

	// Read graph as an adjacency list

	t1 = time(NULL);

	printf("Loading adjacency list from file %s\n", argv[1]);
	
	g2 = read_adjlist(argv[1]);

	printf("Number of nodes: %lu\n", g2->n);
	printf("Number of edges: %lu\n", g2->e);

	printf("Building the adjacency list\n");
	mkadjlist(g2);
	
	free_adjlist(g2);

	t2 = time(NULL);

	printf("- Overall time = %llds\n", (t2-t1)%60);

	// Read graph as an adjacency matrix

	t1 = time(NULL);

	printf("Loading adjacency matrix from file %s\n", argv[1]);

	g3 = read_adjmatrix(argv[1]);

	printf("Number of nodes: %lu\n", g3->n);
	printf("Number of edges: %lu\n", g3->e);

	printf("Building the adjacency matrix\n");
	mkmatrix(g3); //this will surely crash unless the graph is small
	
	free_adjmatrix(g3);

	t2 = time(NULL);

	printf("- Overall time = %llds\n", (t2-t1)%60);

	return 0;
}
