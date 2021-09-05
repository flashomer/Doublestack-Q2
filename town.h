#ifndef TOWN_H
#define TOWN_H

#include <stdbool.h>
#include <stdio.h>

struct person{
  char * name;
  char * address;
};

struct town{
  struct queue* applications;
  struct stack* available;
  struct stack* installed;
};

struct application{
  struct person* person;
  char* date;
};

struct assignedNumber{
  struct person* owner;
  int number;
};

#include "queue.h"
#include "stack.h"

struct town* createTown();

void enqueueApplication(struct town * t, struct application* a);

bool applicationsAvailable(struct town* t);

void processApplication(struct town * t);

void destroyApplication(struct application* a);

void destroyPerson(struct person* p);

void destroyTown(struct town* t);

void removeNumber(struct town* t, int number);

struct assignedNumber* assignNumber(struct person* p, int n);
#endif
