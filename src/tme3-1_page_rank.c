#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "algorithms.h"

int main(int argc, char** argv) {
	spadjmatrix *g;
    time_t t1, t2;
    double alpha = 0.15;
    unsigned long t = 10;

	printf("File: \"%s\".\n", argv[1]);
	
	printf("Loading graph as a sparse adjacency matrix...\n");
	t1 = time(NULL);
	g = read_spadjmatrix(argv[1]);
	mkspmatrix(g);
	t2 = time(NULL);
	printf("Done. Time: %lus.\nNumber of nodes: %lu.\nNumber of edges: %lu.\n", (unsigned long) difftime(t2, t1), g->n, g->e);

    double* P;
    printf("Computing the PageRank with alpha=%.2f and t=%lu...\n", alpha, t);
    t1 = time(NULL);
    P = power_iteration(g, alpha, t);
    t2 = time(NULL);
    printf("Done. Time: %lus.\n", (unsigned long) difftime(t2, t1));

    unsigned long i;
    for (i = 0; i < g->n; i++) printf("%f ", P[i]);
    printf("\n");

    // not sure if it's working correctly...

    free(P);
	free_spadjmatrix(g);
}
