#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "algorithms.h"

int main(int argc, char** argv) {
    adjlist *g;
    time_t t1, t2;
    unsigned long diam;
    unsigned int n_times = 100;

    printf("File: \"%s\".\n", argv[1]);

    printf("Loading graph as an adjacency list...\n");
    t1 = time(NULL);
    g = read_adjlist(argv[1]);
    mkadjlist(g);
    t2 = time(NULL);
    printf("Done. Time: %lus.\n", (unsigned long) difftime(t2, t1));

    printf("Computing diameter lower bound with %u searches...\n", n_times);
    t1 = time(NULL);
    diam = BFS_diameter(g, n_times);
    t2 = time(NULL);
    printf("Done. Time: %lus.\nDiameter lower bound: %lu.\n", (unsigned long) difftime(t2, t1), diam);

    free_adjlist(g);

    return 0;
}
