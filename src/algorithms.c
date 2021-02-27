#include <stdlib.h>
#include <stdio.h>
#include "algorithms.h"
#include "misc.h"
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
        for (i = g->cd[u]; i < g->cd[u+1]; i++) {
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
    for (i = 0; i < n_times; i++) {
        farthest_node(g, node, &node, &dist);
        if (diameter < dist) {
            diameter = dist;
        }
    }
    return diameter;
}

// List all triangles of a graph
unsigned long* list_triangles(adjlist* g, unsigned long* n_triangles) {
    unsigned long *ctd = malloc((g->n+1)*sizeof(unsigned long)); //cumulative truncated degree
    unsigned long *tsl = malloc(2*g->e*sizeof(unsigned long)); //concatenated truncated list of neighbors of all nodes
    unsigned long u;
    unsigned long i, k = 0, max_d = 0;
    ctd[0] = 0;
    for (u = 0; u < g->n; u++) {
        for (i = g->cd[u]; i < g->cd[u+1]; i++) {
            if (g->adj[i] > u) {
                tsl[k] = g->adj[i];
                k++;
            }
        }
        ctd[u+1] = k;
        if (ctd[u+1]-ctd[u] > max_d) max_d = ctd[u+1]-ctd[u];
    }
    tsl = realloc(tsl, k*sizeof(unsigned long));
    unsigned long v;
    unsigned long e;
    unsigned long t = 0;
    unsigned long maxt = 3*NTRIANGLES;
    unsigned long *triangles = malloc(maxt*sizeof(unsigned long));
    unsigned long *W = malloc(max_d*sizeof(unsigned long));
    *n_triangles = 0;
    for (e = 0; e < g->e; e++) {
        u = g->edges[e].s;
        v = g->edges[e].t;
        intersection(tsl+ctd[u], ctd[u+1]-ctd[u], tsl+ctd[v], ctd[v+1]-ctd[v], W, &k);
        *n_triangles += k;
        for (i = 0; i < k; i++) {
            if (t+3 > maxt) {
                maxt += 3*NTRIANGLES;
                triangles = realloc(triangles, maxt*sizeof(unsigned long));
            }
            triangles[t+0] = u;
            triangles[t+1] = v;
            triangles[t+2] = W[i];
            t += 3;
        }
    }
    free(ctd); free(tsl); free(W);
    triangles = realloc(triangles, t*sizeof(unsigned long));
    return triangles;
}
