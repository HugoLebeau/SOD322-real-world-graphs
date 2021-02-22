#include <stdlib.h>
#include <stdio.h>
#include "algorithms.h"
#include "queue.h"

// Compute the distance of the farthest node
void farthest_node(adjlist* g, unsigned long s, unsigned long* res_node, unsigned long* res_dist) {
    unsigned long *dist = calloc(g->n, sizeof(unsigned long));
    fifo *queue = queue_alloc();
    enqueue(s, queue);
    unsigned long u, v;
    unsigned long i;
    while (!is_empty(queue)) {
        u = dequeue(queue);
        for (i=g->cd[u]; i<g->cd[u+1]; i++) {
            v = g->adj[i];
            if (dist[v] == 0 && v != s) {
                enqueue(v, queue);
                dist[v] = dist[u]+1;
            }
        }
    }
    free_queue(queue);
    *res_node = u;
    *res_dist = dist[u];
    free(dist);
}

// Compute a lower bound of the diameter of a graph
unsigned long BFS_diameter(adjlist* g, unsigned int n_times) {
    unsigned long node = 1, diameter = 0, dist;
    unsigned int i;
    for (i=0; i<n_times; i++) {
        farthest_node(g, node, &node, &dist);
        if (diameter < dist) {
            diameter = dist;
        }
    }
    return diameter;
}
