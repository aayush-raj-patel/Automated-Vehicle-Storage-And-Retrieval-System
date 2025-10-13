#ifndef VEHICLE_H
#define VEHICLE_H

#include <stdbool.h>

#define PLATE_LEN 16
#define OWNER_LEN 64

typedef struct Vehicle {
    int id;
    char plate[PLATE_LEN];
    char owner[OWNER_LEN];
} Vehicle;

/* Vehicle manager */
void vehicle_manager_init(void);
Vehicle* vehicle_create(int id, const char* plate, const char* owner);
Vehicle* vehicle_get_by_id(int id);
void vehicle_delete_by_id(int id);
void vehicle_print(Vehicle* v);
void vehicle_print_all(void);

#endif // VEHICLE_H

