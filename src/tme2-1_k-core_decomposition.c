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
    printf("Done. Time: %lus.\nCore value of the graph: %lu.\n", (unsigned long) difftime(t2, t1), core_value[core_ordering[0]]);
    
    double* add = malloc(g->n*sizeof(double));
    double* ed = malloc(g->n*sizeof(double));
    printf("Computing average degree density and edge density of densest core ordering prefix...\n");
    t1 = time(NULL);
    densest_core_ordering_prefix(g, core_ordering, add, ed);
    t2 = time(NULL);
    printf("Done. Time: %lus.\n", (unsigned long) difftime(t2, t1));

    printf("Writing file...\n");
    t1 = time(NULL);
    FILE *file = fopen("outputs/densest_prefix.csv", "w+");
    fprintf(file, "Size,Average degree density,Edge density\n");
    unsigned long p;
    for (p = 0; p < g->n; p++)  fprintf(file, "%lu,%f,%f\n", p+1, add[p], ed[p]);
    fclose(file);
    t2 = time(NULL);
    printf("Done. Time: %lus.\n", (unsigned long) difftime(t2, t1));

    free(core_value);
    free(core_ordering);
    free(add);
    free(ed);
	free_adjlist(g);
}
