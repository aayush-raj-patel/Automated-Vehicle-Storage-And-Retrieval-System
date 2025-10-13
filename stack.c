#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct IntStack {
    int *data;
    int capacity;
    int top;
};

IntStack* stack_create(int capacity) {
    IntStack* s = (IntStack*)malloc(sizeof(IntStack));
    s->data = (int*)malloc(sizeof(int)*capacity);
    s->capacity = capacity;
    s->top = 0;
    return s;
}

void stack_free(IntStack* s) {
    if (!s) return;
    free(s->data);
    free(s);
}

bool stack_push(IntStack* s, int v) {
    if (s->top >= s->capacity) return false;
    s->data[s->top++] = v;
    return true;
}

bool stack_pop(IntStack* s, int* out) {
    if (s->top == 0) return false;
    s->top--;
    if (out) *out = s->data[s->top];
    return true;
}

bool stack_is_empty(IntStack* s) {
    return s->top == 0;
}

int stack_size(IntStack* s) {
    return s->top;
}