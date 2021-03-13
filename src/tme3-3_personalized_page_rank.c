#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <string.h>
#include <time.h>
#include "algorithms.h"

int main(int argc, char** argv) {
	sptmatrix *g;
    time_t t1, t2;
    double alpha = 0.15;
    unsigned long t = 20;

	printf("File: \"%s\".\n", argv[1]);
	
	printf("Loading graph as a sparse transition matrix...\n");
	t1 = time(NULL);
	g = read_sptmatrix(argv[1]);
	mksptmatrix(g);
	t2 = time(NULL);
	printf("Done. Time: %lus.\nNumber of nodes: %lu.\nNumber of edges: %lu.\n", (unsigned long) difftime(t2, t1), g->n, g->e);

    double *P;
    double *P0 = calloc(g->n, sizeof(double));
    P0[atoi(argv[2])] = 1.;
    printf("Computing the PageRank with alpha=%.2f and t=%lu...\n", alpha, t);
    t1 = time(NULL);
    P = power_iteration(g, alpha, t, P0);
    t2 = time(NULL);
    printf("Done. Time: %lus.\n", (unsigned long) difftime(t2, t1));

    printf("Writing file...\n");
    t1 = time(NULL);
    FILE *file = fopen("outputs/rooted_page_rank.csv", "w+");
    fprintf(file, "Node,RootedPageRank\n");
    unsigned long i;
    for (i = 0; i < g->n; i++) fprintf(file, "%lu,%.*e\n", i, DECIMAL_DIG, P[i]);
    fclose(file);
    t2 = time(NULL);
    printf("Done. Time: %lus.\n", (unsigned long) difftime(t2, t1));

    free(P);
    free(P0);
	free_sptmatrix(g);
}
