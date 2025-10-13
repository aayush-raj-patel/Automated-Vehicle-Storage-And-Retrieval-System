#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Slot* head = NULL;
static int total_slots_count = 0;

void slots_init(int total_slots) {
    // free old list
    Slot* cur = head;
    while (cur) {
        Slot* tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    head = NULL;

    // create linked list with IDs 0..total_slots-1
    Slot* prev = NULL;
    for (int i = 0; i < total_slots; ++i) {
        Slot* s = (Slot*)malloc(sizeof(Slot));
        s->id = i;
        s->is_free = 1;
        s->vehicle_id = -1;
        s->next = NULL;
        if (!head) head = s;
        if (prev) prev->next = s;
        prev = s;
    }
    total_slots_count = total_slots;
}

Slot* slots_find_free(void) {
    Slot* cur = head;
    while (cur) {
        if (cur->is_free) return cur;
        cur = cur->next;
    }
    return NULL;
}

Slot* slots_find_by_id(int id) {
    Slot* cur = head;
    while (cur) {
        if (cur->id == id) return cur;
        cur = cur->next;
    }
    return NULL;
}

Slot* slots_find_by_vehicle(int vehicle_id) {
    Slot* cur = head;
    while (cur) {
        if (!cur->is_free && cur->vehicle_id == vehicle_id) return cur;
        cur = cur->next;
    }
    return NULL;
}

int slots_occupy(Slot* s, int vehicle_id) {
    if (!s) return -1;
    if (!s->is_free) return -2;
    s->is_free = 0;
    s->vehicle_id = vehicle_id;
    return s->id;
}

int slots_free_slot(Slot* s) {
    if (!s) return -1;
    if (s->is_free) return -2;
    s->is_free = 1;
    s->vehicle_id = -1;
    return s->id;
}

void slots_print_all(void) {
    printf("=== Slots ===\n");
    Slot* cur = head;
    while (cur) {
        printf("Slot %3d | %s", cur->id, cur->is_free ? "FREE   " : "OCCUPIED");
        if (!cur->is_free) printf(" | Vehicle ID: %d", cur->vehicle_id);
        printf("\n");
        cur = cur->next;
    }
}

int slots_total(void) {
    return total_slots_count;
}