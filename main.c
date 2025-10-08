#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vehicle.h"
#include "queue.h"
#include "stack.h"
#include "linkedlist.h"
#include "graph.h"
#include "bfs_dfs.h"

/* Simple config */
#define TOTAL_SLOTS 20
#define ENTRY_NODE 0
#define QUEUE_CAP 128
#define STACK_CAP 128

static IntQueue* entry_queue = NULL;
static IntQueue* exit_queue = NULL;
static IntStack* floor_stack = NULL;
static Graph* parking_graph = NULL;

static int next_vehicle_id = 1;

void init_system(void) {
    vehicle_manager_init();
    slots_init(TOTAL_SLOTS);
    parking_graph = graph_create(TOTAL_SLOTS);
    // Simple sample edges: create a linear layout for demonstration
    for (int i = 0; i < TOTAL_SLOTS - 1; ++i) {
        graph_add_edge(parking_graph, i, i+1);
    }
    entry_queue = queue_create(QUEUE_CAP);
    exit_queue = queue_create(QUEUE_CAP);
    floor_stack = stack_create(STACK_CAP);
    // push all slots into stack to simulate vertical LIFO floors (optional)
    for (int i = 0; i < TOTAL_SLOTS; ++i) stack_push(floor_stack, TOTAL_SLOTS - 1 - i);
}

void shutdown_system(void) {
    queue_free(entry_queue);
    queue_free(exit_queue);
    stack_free(floor_stack);
    graph_free(parking_graph);
    // Note: vehicle memory freed on program end (not strictly necessary)
}

void process_next_entry(void) {
    int vid;
    if (!queue_dequeue(entry_queue, &vid)) {
        printf("No vehicles waiting in entry queue.\n");
        return;
    }
    // find nearest free slot using BFS from ENTRY_NODE
    int slot = find_nearest_free_slot(parking_graph, ENTRY_NODE);
    if (slot < 0) {
        printf("No free slots available. Putting vehicle back into queue.\n");
        queue_enqueue(entry_queue, vid);
        return;
    }
    Slot* s = slots_find_by_id(slot);
    if (!s) {
        printf("Error: invalid slot found.\n");
        return;
    }
    slots_occupy(s, vid);
    printf("Vehicle %d assigned to slot %d\n", vid, slot);
}

void add_vehicle_interactively(void) {
    char plate[PLATE_LEN];
    char owner[OWNER_LEN];
    printf("Enter plate: ");
    if (scanf(" %15s", plate) != 1) { printf("Invalid input\n"); return; }
    printf("Enter owner name (no spaces): ");
    if (scanf(" %63s", owner) != 1) { printf("Invalid input\n"); return; }
    int vid = next_vehicle_id++;
    vehicle_create(vid, plate, owner);
    if (!queue_enqueue(entry_queue, vid)) {
        printf("Entry queue full — cannot add vehicle.\n");
        vehicle_delete_by_id(vid);
        return;
    }
    printf("Vehicle queued with ID %d\n", vid);
}

void retrieve_vehicle_interactively(void) {
    int vid;
    printf("Enter vehicle id to retrieve: ");
    if (scanf("%d", &vid) != 1) { printf("Invalid input\n"); return; }
    // locate via DFS
    int slot = search_vehicle_dfs(parking_graph, vid);
    if (slot < 0) {
        // fallback: check slot list directly
        Slot* s = slots_find_by_vehicle(vid);
        if (s) slot = s->id;
    }
    if (slot < 0) {
        printf("Vehicle %d not found in parking.\n", vid);
        return;
    }
    Slot* s = slots_find_by_id(slot);
    if (!s) { printf("Invalid slot\n"); return; }
    slots_free_slot(s);
    queue_enqueue(exit_queue, vid);
    printf("Vehicle %d retrieved from slot %d and added to exit queue.\n", vid, slot);
    // Optionally delete vehicle record here if persistence not needed:
    vehicle_delete_by_id(vid);
}

void show_menu(void) {
    printf("\n--- AVSRS Menu ---\n");
    printf("1. Add vehicle to entry queue\n");
    printf("2. Process next entry (assign slot)\n");
    printf("3. Retrieve vehicle by ID\n");
    printf("4. Show parking map (graph)\n");
    printf("5. Show slots\n");
    printf("6. Show vehicles\n");
    printf("7. Show entry/exit queue sizes\n");
    printf("0. Exit\n");
    printf("------------------\n");
    printf("Choice: ");
}

int main(void) {
    init_system();
    int choice;
    while (1) {
        show_menu();
        if (scanf("%d", &choice) != 1) {
            // flush bad input
            int c; while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        switch (choice) {
            case 1:
                add_vehicle_interactively();
                break;
            case 2:
                process_next_entry();
                break;
            case 3:
                retrieve_vehicle_interactively();
                break;
            case 4:
                graph_print(parking_graph);
                break;
            case 5:
                slots_print_all();
                break;
            case 6:
                vehicle_print_all();
                break;
            case 7:
                printf("Entry queue size: %d | Exit queue size: %d\n", queue_size(entry_queue), queue_size(exit_queue));
                break;
            case 0:
                shutdown_system();
                printf("Exiting.\n");
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}