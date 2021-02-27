#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "algorithms.h"

int main(int argc, char** argv) {
	adjlist *g;
    time_t t1, t2;
    unsigned long n_triangles;
    unsigned long *triangles;

	printf("File: \"%s\".\n", argv[1]);

    printf("Loading graph as an adjacency list...\n");
    t1 = time(NULL);
    g = read_adjlist(argv[1]);
    mkadjlist(g);
    t2 = time(NULL);
    printf("Done. Time: %lus.\n", (unsigned long) difftime(t2, t1));

    printf("Sorting neighbors...\n");
    t1 = time(NULL);
    sort_neighbors(g);
    t2 = time(NULL);
    printf("Done. Time: %lus.\n", (unsigned long) difftime(t2, t1));
    
    printf("Listing triangles...\n");
    t1 = time(NULL);
    triangles = list_triangles(g, &n_triangles);
    t2 = time(NULL);
    printf("Done. Time: %lus.\nNumber of triangles: %lu.\n", (unsigned long) difftime(t2, t1), n_triangles);
    //unsigned long t; for (t = 0; t < 3*n_triangles; t += 3) printf("%lu %lu %lu\n", triangles[t+0], triangles[t+1], triangles[t+2]);
	
    free(triangles);
	free_adjlist(g);

	return 0;
}
