#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "algorithms.h"

int main(int argc, char** argv) {
    srand(time(NULL));
	adjlist *g;
    time_t t1, t2;

    unsigned long n_clusters = 4;
    unsigned long n_nodes_per_cluster = 100;
    double p = 0.9;
    double q = 0.01;

    printf("Generating graph...\n");
    t1 = time(NULL);
    g = gen_graph(n_clusters, n_nodes_per_cluster, p, q);
    t2 = time(NULL);
    printf("Done. Time: %lus.\nNumber of nodes: %lu.\nNumber of edges: %lu.\n", (unsigned long) difftime(t2, t1), g->n, g->e);

    printf("Writing file...\n");
    t1 = time(NULL);
    FILE *file = fopen("outputs/gen_graph.csv", "w+");
    unsigned long i;
    for (i = 0; i < g->e; i++) fprintf(file, "%lu %lu\n", g->edges[i].s, g->edges[i].t);
    fclose(file);
    t2 = time(NULL);
    printf("Done. Time: %lus.\n", (unsigned long) difftime(t2, t1));

	free_adjlist(g);

    return 0;
}
