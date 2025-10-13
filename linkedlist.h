#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>

typedef struct Slot {
    int id;             // unique slot id
    int is_free;        // 1 free, 0 occupied
    int vehicle_id;     // id of occupying vehicle (-1 if none)
    struct Slot* next;
} Slot;

/* Slot list manager */
void slots_init(int total_slots);
Slot* slots_find_free(void);
Slot* slots_find_by_id(int id);
Slot* slots_find_by_vehicle(int vehicle_id);
int slots_occupy(Slot* s, int vehicle_id);
int slots_free_slot(Slot* s);
void slots_print_all(void);
int slots_total(void);

#endif // LINKEDLIST_H