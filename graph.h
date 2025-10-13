#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct Graph Graph;

/* Create graph with n nodes (node ids 0..n-1) */
Graph* graph_create(int n);
void graph_free(Graph* g);
bool graph_add_edge(Graph* g, int u, int v); // undirected edge
void graph_print(Graph* g);
int graph_nodes(Graph* g);

#endif // GRAPH_H