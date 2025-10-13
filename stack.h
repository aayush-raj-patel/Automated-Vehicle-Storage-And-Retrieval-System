#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct IntStack IntStack;

IntStack* stack_create(int capacity);
void stack_free(IntStack* s);
bool stack_push(IntStack* s, int v);
bool stack_pop(IntStack* s, int* out);
bool stack_is_empty(IntStack* s);
int stack_size(IntStack* s);

#endif // STACK_H