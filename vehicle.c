#include "vehicle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* A simple dynamic array of pointers for vehicle storage */
static Vehicle** vehicles = NULL;
static int vehicles_capacity = 0;
static int vehicles_count = 0;

void vehicle_manager_init(void) {
    vehicles_capacity = 128;
    vehicles = (Vehicle**)calloc(vehicles_capacity, sizeof(Vehicle*));
    vehicles_count = 0;
}

static void ensure_capacity(int id) {
    if (id >= vehicles_capacity) {
        int newcap = vehicles_capacity;
        while (id >= newcap) newcap *= 2;
        vehicles = (Vehicle**)realloc(vehicles, newcap * sizeof(Vehicle*));
        for (int i = vehicles_capacity; i < newcap; ++i) vehicles[i] = NULL;
        vehicles_capacity = newcap;
    }
}

Vehicle* vehicle_create(int id, const char* plate, const char* owner) {
    if (id < 0) return NULL;
    ensure_capacity(id);
    if (vehicles[id] != NULL) {
        // overwrite existing
        free(vehicles[id]);
        vehicles[id] = NULL;
    }
    Vehicle* v = (Vehicle*)malloc(sizeof(Vehicle));
    v->id = id;
    strncpy(v->plate, plate, PLATE_LEN-1);
    v->plate[PLATE_LEN-1] = '\0';
    strncpy(v->owner, owner, OWNER_LEN-1);
    v->owner[OWNER_LEN-1] = '\0';
    vehicles[id] = v;
    if (id >= vehicles_count) vehicles_count = id+1;
    return v;
}

Vehicle* vehicle_get_by_id(int id) {
    if (id < 0 || id >= vehicles_capacity) return NULL;
    return vehicles[id];
}

void vehicle_delete_by_id(int id) {
    if (id < 0 || id >= vehicles_capacity) return;
    if (vehicles[id] != NULL) {
        free(vehicles[id]);
        vehicles[id] = NULL;
    }
}

void vehicle_print(Vehicle* v) {
    if (!v) { printf("No vehicle\n"); return; }
    printf("Vehicle ID: %d | Plate: %s | Owner: %s\n", v->id, v->plate, v->owner);
}

void vehicle_print_all(void) {
    printf("=== Vehicles ===\n");
    for (int i = 0; i < vehicles_capacity; ++i) {
        if (vehicles[i]) vehicle_print(vehicles[i]);
    }
}
