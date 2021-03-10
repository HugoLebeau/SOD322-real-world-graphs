#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "algorithms.h"

int main(int argc, char** argv) {
	adjlist *g;
    time_t t1, t2;

	printf("File: \"%s\".\n", argv[1]);
	
	printf("Loading graph as an adjacency list...\n");
	t1 = time(NULL);
	g = read_adjlist(argv[1]);
	mkadjlist(g);
	t2 = time(NULL);
	printf("Done. Time: %lus.\nNumber of nodes: %lu.\nNumber of edges: %lu.\n", (unsigned long) difftime(t2, t1), g->n, g->e);

    printf("Computing the min heap of the graph...\n");
    t1 = time(NULL);
    sort_nodes(g);
    t2 = time(NULL);
    printf("Done. Time: %lus.\n", (unsigned long) difftime(t2, t1));
    
    unsigned long *core_value = malloc(g->n*sizeof(unsigned long));
    unsigned long *core_ordering = malloc(g->n*sizeof(unsigned long));
    printf("Computing the core decomposition...\n");
    t1 = time(NULL);
    core_decomposition(g, core_value, core_ordering);
    t2 = time(NULL);
    printf("Done. Time: %lus.\n", (unsigned long) difftime(t2, t1));

    unsigned long i;
    for (i = 0; i < g->n; i++) printf("%lu ", core_ordering[i]);
    printf("\n");
    for (i = 0; i < g->n; i++) printf("%lu ", core_value[i]);
    printf("\n");

    unsigned long cv = core_value[core_ordering[0]]; //core value of the graph
    unsigned long p = 1; //size of the densest prefix
    while (core_value[core_ordering[p]] == cv) p++;
    double add_ = cv/2.; //average degree density of the densest prefix
    double ed_ = cv/(p-1.); //edge density of the densest prefix

    printf("Core value of the graph: %lu.\n", cv);
    printf("Densest prefix\n");
    printf("\t- size: %lu\n", p);
    printf("\t- average degree density: %.1f\n", add_);
    printf("\t- edge density: %f\n", ed_);

    double* add = malloc(g->n*sizeof(double));
    double* ed = malloc(g->n*sizeof(double));
    densest_core_ordering_prefix(g, core_ordering, add, ed);

    for (i = 0; i < g->n; i++) printf("%f ", add[i]);
    printf("\n");
    for (i = 0; i < g->n; i++) printf("%f ", ed[i]);
    printf("\n");

    free(core_value);
    free(core_ordering);
    free(add);
    free(ed);
	free_adjlist(g);
}
