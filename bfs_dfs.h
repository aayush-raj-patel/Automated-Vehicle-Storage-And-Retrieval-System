#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct AdjNode {
    int v;
    struct AdjNode* next;
} AdjNode;

struct Graph {
    int n;
    AdjNode** adj;
};

Graph* graph_create(int nodes) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->n = nodes;
    g->adj = (AdjNode**)calloc(nodes, sizeof(AdjNode*));
    return g;
}

void graph_add_edge(Graph* g, int src, int dest) {
    AdjNode* node = (AdjNode*)malloc(sizeof(AdjNode));
    node->v = dest;
    node->next = g->adj[src];
    g->adj[src] = node;
}

int graph_nodes(Graph* g) {
    return g->n;
}

void graph_print(Graph* g) {
    for (int i = 0; i < g->n; ++i) {
        printf("Node %d: ", i);
        AdjNode* cur = g->adj[i];
        while (cur) {
            printf("%d ", cur->v);
            cur = cur->next;
        }
        printf("\n");
    }
}

void graph_free(Graph* g) {
    for (int i = 0; i < g->n; ++i) {
        AdjNode* cur = g->adj[i];
        while (cur) {
            AdjNode* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(g->adj);
    free(g);
}
