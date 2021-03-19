#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "algorithms.h"

int main(int argc, char** argv) {
    srand(time(NULL));
	adjlist *g;
    time_t t1, t2;

	printf("File: \"%s\".\n", argv[1]);
	
	printf("Loading graph as an adjacency list...\n");
	t1 = time(NULL);
	g = read_adjlist(argv[1]);
	mkadjlist(g);
	t2 = time(NULL);
	printf("Done. Time: %lus.\nNumber of nodes: %lu.\nNumber of edges: %lu.\n", (unsigned long) difftime(t2, t1), g->n, g->e);

    unsigned long *label;
    printf("Computing label propagation...\n");
    t1 = time(NULL);
    label = label_propagation(g);
    t2 = time(NULL);
    printf("Done. Time: %lus.\n", (unsigned long) difftime(t2, t1));

    printf("Writing file...\n");
    t1 = time(NULL);
    FILE *file = fopen("outputs/labels.csv", "w+");
    fprintf(file, "Node,Label\n");
    unsigned long i;
    for (i = 0; i < g->n; i++) fprintf(file, "%lu,%lu\n", i, label[i]);
    fclose(file);
    t2 = time(NULL);
    printf("Done. Time: %lus.\n", (unsigned long) difftime(t2, t1));

	free_adjlist(g);
    free(label);

    return 0;
}
