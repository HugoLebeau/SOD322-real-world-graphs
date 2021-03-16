#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "graph.h"

#define NTRIANGLES 100000000

unsigned long BFS_diameter(adjlist* g, unsigned int n_times);
unsigned long* list_triangles(adjlist* g, unsigned long* n_triangles);
void core_decomposition(adjlist* g, unsigned long* core_value, unsigned long* ordering);
void densest_core_ordering_prefix(adjlist* g, unsigned long* core_ordering, double* add, double* ed);
double* power_iteration(sptmatrix* g, double alpha, unsigned long t, double* P0);
adjlist* gen_graph(unsigned long n_clusters, unsigned long n_nodes_per_cluster, double p, double q);

#endif
