#ifndef BFS_DFS_H
#define BFS_DFS_H

#include "graph.h"
#include "linkedlist.h"

/* find_nearest_free_slot:
 *  - uses BFS starting from 'start_node' (an entry node)
 *  - returns slot id (>=0) if found, or -1 if none available
 */
int find_nearest_free_slot(Graph* g, int start_node);

/* search_vehicle_dfs:
 *  - search the graph for the slot containing vehicle_id using DFS.
 *  - returns slot id if found, -1 otherwise.
 *  - this is just a traversal-based search (uses slots_find_by_vehicle if you want O(n) instead)
 */
int search_vehicle_dfs(Graph* g, int vehicle_id);

#endif // BFS_DFS_H
