#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

#include "town.h"

#define QUEUE_SIZE 4

struct queue{
  int bottom;
  int top;
  int size;
  struct application* data[QUEUE_SIZE];
};

struct queue* createQueue();
void destroyQueue(struct queue* queue);
void enqueue(struct queue* queue, struct application* application);
struct application* dequeue(struct queue* queue);
bool isQueueEmpty(struct queue* queue);
bool isQueueFull(struct queue* queue);
#endif
