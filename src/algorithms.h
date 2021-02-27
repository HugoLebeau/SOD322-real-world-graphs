#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "graph.h"

#define NTRIANGLES 100000000

unsigned long BFS_diameter(adjlist* g, unsigned int n_times);
unsigned long* list_triangles(adjlist* g, unsigned long* n_triangles);

#endif
