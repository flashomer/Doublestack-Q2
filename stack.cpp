#include "stack.h"

void initializeStack(struct stack* stack){
  stack->top = -1;
}

bool isStackEmpty(struct stack* stack){
  return stack->top == -1;
}

void pushPointer(struct stack* stack, void* ptr){
  stack->data[++stack->top] = ptr;
}

void* popPointer(struct stack* stack){
  return stack->data[stack->top--];
}

void pushInt(struct stack* stack, int val){
  //Copy to memory and push pointer
  int* ptr = (int*)malloc(sizeof(int));
  *ptr = val;
  pushPointer(stack, ptr);
}

void pushAssignedNumber(struct stack* stack, struct assignedNumber* person){
  pushPointer(stack, person);
}

int popInt(struct stack* stack){
  //Pop pointer, copy from memory and free
  int* ptr = (int*) popPointer(stack);
  int res = *ptr;
  free(ptr);
  return res;
}

struct assignedNumber* popAssignedNumber(struct stack* stack){
  struct assignedNumber* ptr = (struct assignedNumber*) popPointer(stack);
  return ptr;
}

void** getPointerToIndex(struct stack* stack, int index){
  return &stack->data[index];
}
