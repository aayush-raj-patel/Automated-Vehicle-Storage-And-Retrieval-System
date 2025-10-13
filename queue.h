#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef struct IntQueue IntQueue;

IntQueue* queue_create(int capacity);
void queue_free(IntQueue* q);
bool queue_enqueue(IntQueue* q, int value);
bool queue_dequeue(IntQueue* q, int* out);
bool queue_is_empty(IntQueue* q);
bool queue_is_full(IntQueue* q);
int queue_size(IntQueue* q);

#endif // QUEUE_H