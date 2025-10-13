#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct IntQueue {
    int *data;
    int capacity;
    int head;
    int tail;
    int size;
};

IntQueue* queue_create(int capacity) {
    IntQueue* q = (IntQueue*)malloc(sizeof(IntQueue));
    q->data = (int*)malloc(sizeof(int)*capacity);
    q->capacity = capacity;
    q->head = 0;
    q->tail = 0;
    q->size = 0;
    return q;
}

void queue_free(IntQueue* q) {
    if (!q) return;
    free(q->data);
    free(q);
}

bool queue_enqueue(IntQueue* q, int value) {
    if (q->size == q->capacity) return false;
    q->data[q->tail] = value;
    q->tail = (q->tail + 1) % q->capacity;
    q->size++;
    return true;
}

bool queue_dequeue(IntQueue* q, int* out) {
    if (q->size == 0) return false;
    if (out) *out = q->data[q->head];
    q->head = (q->head + 1) % q->capacity;
    q->size--;
    return true;
}

bool queue_is_empty(IntQueue* q) {
    return q->size == 0;
}

bool queue_is_full(IntQueue* q) {
    return q->size == q->capacity;
}

int queue_size(IntQueue* q) {
    return q->size;
}