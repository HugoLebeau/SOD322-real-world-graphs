#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "algorithms.h"

int main(int argc, char** argv) {
	sptmatrix *g;
    time_t t1, t2;
    double alpha[5] = {0.15, 0.1, 0.2, 0.5, 0.9};
    unsigned long t = 20;

	printf("File: \"%s\".\n", argv[1]);
	
	printf("Loading graph as a sparse transition matrix...\n");
	t1 = time(NULL);
	g = read_sptmatrix(argv[1]);
	mksptmatrix(g);
	t2 = time(NULL);
	printf("Done. Time: %lus.\nNumber of nodes: %lu.\nNumber of edges: %lu.\n", (unsigned long) difftime(t2, t1), g->n, g->e);

    double **P = malloc(5*sizeof(double*));
    unsigned long i, j;
    for (i = 0; i < 5; i++) {
        printf("Computing the PageRank with alpha=%.2f and t=%lu...\n", alpha[i], t);
        t1 = time(NULL);
        P[i] = power_iteration(g, alpha[i], t);
        t2 = time(NULL);
        printf("Done. Time: %lus.\n", (unsigned long) difftime(t2, t1));
    }

    printf("Saving in and out degrees...\n");
    t1 = time(NULL);
    unsigned long *d_in = calloc(g->n, sizeof(unsigned long));
    unsigned long *d_out = calloc(g->n, sizeof(unsigned long));
    for (i = 0; i < g->e; i++) {
        d_in[g->edges[i].t]++;
        d_out[g->edges[i].s]++;
    }
    t2 = time(NULL);
    printf("Done. Time: %lus.\n", (unsigned long) difftime(t2, t1));

    printf("Writing file...\n");
    t1 = time(NULL);
    FILE *file = fopen("outputs/page_rank.csv", "w+");
    fprintf(file, "Node,In-degree,Out-degree");
    for (j = 0; j < 5; j++) fprintf(file, ",%.2f", alpha[j]);
    fprintf(file, "\n");
    for (i = 0; i < g->n; i++) {
        fprintf(file, "%lu,%lu,%lu", i, d_in[i], d_out[i]);
        for (j = 0; j < 5; j++) fprintf(file, ",%f", P[j][i]);
        fprintf(file, "\n");
    }
    fclose(file);
    t2 = time(NULL);
    printf("Done. Time: %lus.\n", (unsigned long) difftime(t2, t1));

    for (i = 0; i < 5; i++) free(P[i]);
    free(P);
	free_sptmatrix(g);
}
