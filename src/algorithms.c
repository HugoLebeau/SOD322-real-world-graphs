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
        for (i = g->cd[u]; i < g->cd[u+1]; i++) { //for each neighbor of u
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
        if (diameter < dist) diameter = dist;
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
    for (u = 0; u < g->n; u++) { //for each node u
        for (i = g->cd[u]; i < g->cd[u+1]; i++) { //for each neighbor of u
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
    for (e = 0; e < g->e; e++) { //for each edge e
        u = g->edges[e].s;
        v = g->edges[e].t;
        intersection(tsl+ctd[u], ctd[u+1]-ctd[u], tsl+ctd[v], ctd[v+1]-ctd[v], W, &k);
        *n_triangles += k;
        for (i = 0; i < k; i++) { //for each node in the intersection
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

// Core decomposition of the graph
// The min heap of the graph is supposed computed
// core_value and core_ordering are supposed to be two arrays of size g->n
void core_decomposition(adjlist* g, unsigned long* core_value, unsigned long* core_ordering) {
    unsigned long i = g->n-1, c = 0;
    unsigned long j, neighbor;
    node v;
    while (g->mh->size > 0) {
        v = extract_min(g->mh);
        if (c < v.d) c = v.d;
        for (j = g->cd[v.n]; j < g->cd[v.n+1]; j++) {
            neighbor = g->adj[j];
            if (g->mh->in[neighbor]) decrease_degree(g->mh, g->mh->where[neighbor]);
        }
        core_value[v.n] = c;
        core_ordering[i] = v.n;
        i--;
    }
}

// Compute the average degree denstity and edge density of each densest core ordering prefix
// add and ed are supposed to be two arrays of size g->n
void densest_core_ordering_prefix(adjlist* g, unsigned long* core_ordering, double* add, double* ed) {
    unsigned long p, degree, i;
    double e = g->e, n = g->n;
    unsigned long *delta = calloc(g->n, sizeof(unsigned long));
    for (p = g->n-1; p > 0; p--) {
        add[p] = e/n; //average degree density
        ed[p] = 2.*e/(n*(n-1)); //edge density
        n -= 1.; //remove one node
        degree = g->cd[core_ordering[p]+1]-g->cd[core_ordering[p]]; //degree of the node removed
        e -= (double) (degree-delta[core_ordering[p]]); //remove edges
        for (i = g->cd[core_ordering[p]]; i < g->cd[core_ordering[p]+1]; i++) delta[g->adj[i]]++; //count edges not to be removed again
    }
}

void swap_pdouble(double** a, double** b) {
    double *buffer;
    buffer = *a;
    *a = *b;
    *b = buffer;
}

// Compute the (personalized) PageRank with the power iteration method
double* power_iteration(sptmatrix* g, double alpha, unsigned long t, double* P0) {
    double *P = malloc(g->n*sizeof(double));
    double *P_res = malloc(g->n*sizeof(double));
    unsigned long k, i;
    double norm1, n = g->n;
    for (i = 0; i < g->n; i++) P[i] = 1./n;
    for (k = 0; k < t; k++) {
        matvecprod(g->mat, P, P_res);
        swap_pdouble(&P, &P_res);
        norm1 = 0.;
        for (i = 0; i < g->n; i++) {
            P[i] = (1.-alpha)*P[i]+alpha*P0[i];
            norm1 += P[i];
        }
        for (i = 0; i < g->n; i++) P[i] += P0[i]*(1.-norm1);
    }
    free(P_res);
    return P;
}
