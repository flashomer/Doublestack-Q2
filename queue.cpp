#include "queue.h"

struct queue* createQueue(){
  struct queue* queue = (struct queue*)malloc(sizeof(struct queue));

  //Set top and bottom
  queue->top = 0;
  queue->bottom = 0;
  queue->size = 0;
  return queue;
}

void destroyQueue(struct queue* queue){
  //Destroy all applications first
  while(!isQueueEmpty(queue)){
    struct application* a = dequeue(queue);
    destroyApplication(a);
  }
  free(queue);
}

void enqueue(struct queue* queue, struct application* application){
  queue->data[queue->top++] = application;
  queue->top %= QUEUE_SIZE;
  queue->size++;
}

struct application* dequeue(struct queue* queue){
  struct application* a = queue->data[queue->bottom++];
  queue->bottom %= QUEUE_SIZE;
  queue->size--;
  return a;
}

bool isQueueEmpty(struct queue* queue){
  return queue->size == 0;
}

bool isQueueFull(struct queue* queue){
  return queue->size == QUEUE_SIZE;
}
