#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct AdjNode {
    int v;
    struct AdjNode* next;
} AdjNode;

struct Graph {
    int n;
    AdjNode** adj;
};

Graph* graph_create(int n) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->n = n;
    g->adj = (AdjNode**)calloc(n, sizeof(AdjNode*));
    return g;
}

void graph_free(Graph* g) {
    if (!g) return;
    for (int i = 0; i < g->n; ++i) {
        AdjNode* cur = g->adj[i];
        while (cur) {
            AdjNode* tmp = cur->next;
            free(cur);
            cur = tmp;
        }
    }
    free(g->adj);
    free(g);
}

bool graph_add_edge(Graph* g, int u, int v) {
    if (!g) return false;
    if (u < 0 || v < 0 || u >= g->n || v >= g->n) return false;
    // add u->v
    AdjNode* a1 = (AdjNode*)malloc(sizeof(AdjNode));
    a1->v = v;
    a1->next = g->adj[u];
    g->adj[u] = a1;
    // add v->u (undirected)
    AdjNode* a2 = (AdjNode*)malloc(sizeof(AdjNode));
    a2->v = u;
    a2->next = g->adj[v];
    g->adj[v] = a2;
    return true;
}

void graph_print(Graph* g) {
    if (!g) return;
    printf("=== Graph adjacency ===\n");
    for (int i = 0; i < g->n; ++i) {
        printf("%d:", i);
        AdjNode* cur = g->adj[i];
        while (cur) {
            printf(" %d", cur->v);
            cur = cur->next;
        }
        printf("\n");
    }
}

int graph_nodes(Graph* g) {
    if (!g) return 0;
    return g->n;
}