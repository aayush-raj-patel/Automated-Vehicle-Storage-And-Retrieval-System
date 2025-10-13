#include "bfs_dfs.h"
#include "graph.h"
#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct AdjNode {
    int v;
    struct AdjNode* next;
} AdjNode;

typedef struct GraphInternal {
    int n;
    AdjNode** adj;
} GraphInternal;

// BFS: find nearest free slot
int find_nearest_free_slot(Graph* g, int start_node) {
    if (!g) return -1;

    GraphInternal* gi = (GraphInternal*)g;
    int n = gi->n;
    int *visited = (int*)calloc(n, sizeof(int));
    int *queue = (int*)malloc(sizeof(int) * n);
    int qh = 0, qt = 0;

    queue[qt++] = start_node;
    visited[start_node] = 1;

    while (qh < qt) {
        int u = queue[qh++];
        Slot* s = slots_find_by_id(u);

        if (s && s->is_free) {
            free(visited);
            free(queue);
            return u;
        }

        AdjNode* cur = gi->adj[u];
        while (cur) {
            int v = cur->v;
            if (!visited[v]) {
                visited[v] = 1;
                queue[qt++] = v;
            }
            cur = cur->next;
        }
    }

    free(visited);
    free(queue);
    return -1;
}

// DFS helper
static int dfs_helper(AdjNode* const *adj, int n, int u, int visited[], int vehicle_id) {
    visited[u] = 1;
    Slot* s = slots_find_by_id(u);

    if (s && !s->is_free && s->vehicle_id == vehicle_id)
        return u;

    AdjNode* cur = adj[u];
    while (cur) {
        int v = cur->v;
        if (!visited[v]) {
            int found = dfs_helper(adj, n, v, visited, vehicle_id);
            if (found >= 0) return found;
        }
        cur = cur->next;
    }
    return -1;
}

// DFS: search vehicle
int search_vehicle_dfs(Graph* g, int vehicle_id) {
    if (!g) return -1;

    GraphInternal* gi = (GraphInternal*)g;
    int n = gi->n;
    int* visited = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            int found = dfs_helper(gi->adj, n, i, visited, vehicle_id);
            if (found >= 0) {
                free(visited);
                return found;
            }
        }
    }

    free(visited);
    return -1;
}
