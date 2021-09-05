#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdbool.h>
#include "town.h"

#define STACK_SIZE 1024

struct stack{
  void* data[STACK_SIZE];
  int top;
};

void initializeStack(struct stack* stack);

bool isStackEmpty(struct stack* stack);

void pushInt(struct stack* stack, int val);
void pushAssignedNumber(struct stack* stack, struct assignedNumber* person);

int popInt(struct stack* stack);
struct assignedNumber* popAssignedNumber(struct stack* stack);

void** getPointerToIndex(struct stack* stack, int index);
#endif
