#include "town.h"

struct town* createTown(){
  struct town* town = (struct town*)malloc(sizeof(struct town));
  town->available = (struct stack*)malloc(sizeof(struct stack));
  town->installed = (struct stack*)malloc(sizeof(struct stack));
  town->applications = createQueue();
  initializeStack(town->available);
  initializeStack(town->installed);

  for(int i = 0;i<1000;i++){
    pushInt(town->available, i);
  }
  return town;
}

void enqueueApplication(struct town * t, struct application* a){
  enqueue(t->applications, a);
}

bool applicationsAvailable(struct town* t){
  return !isQueueEmpty(t->applications);
}

void processApplication(struct town * t){
  if(isQueueEmpty(t->applications)) return;

  struct application* a = dequeue(t->applications);
  struct person* p = a->person;

  printf("\n\nProcessing application:\n");
  printf("Name: %s\n", p->name);
  printf("Address: %s\n", p->address);
  printf("Date: %s\n", a->date);

  int number = popInt(t->available);
  printf("\nAssigned number: %d\n", number);

  struct assignedNumber* assigned = assignNumber(p, number);
  pushAssignedNumber(t->installed, assigned);

  destroyApplication(a);

  printf("\n\n");
}

void destroyApplication(struct application* a){
  free(a->date);
  free(a);
}

void destroyPerson(struct person* p){
  free(p->name);
  free(p->address);
  free(p);
}

void destroyTown(struct town* t){
  while(!isStackEmpty(t->available)){
    popInt(t->available);
  }
  free(t->available);

  while(!isStackEmpty(t->installed)){
    struct assignedNumber* assigned = popAssignedNumber(t->installed);
    destroyPerson(assigned->owner);
    free(assigned);
  }
  free(t->installed);

  destroyQueue(t->applications);

  free(t);
}

void removeNumber(struct town* t, int number){
  void** top = getPointerToIndex(t->installed, t->installed->top);
  void** ptr;
  for(int i = 0;i <= t->installed->top;i++){
    ptr = getPointerToIndex(t->installed, i);
    struct assignedNumber* assigned = ((struct assignedNumber*)*ptr);
    if(assigned->number == number){
      //Swap number to be removed with top of the stack
      void * tmp = *top;
      *top = *ptr;
      *ptr = tmp;

      assigned = popAssignedNumber(t->installed);
      struct person* p = assigned->owner;

      printf("\n\nRemoved assigned number:\n");
      printf("Name: %s\n", p->name);
      printf("Address: %s\n", p->address);
      printf("Number: %d\n", assigned->number);

      destroyPerson(p);
      free(assigned);
      return;
    }
  }
  printf("There is no such number installed.\n");
}

struct assignedNumber* assignNumber(struct person* p, int n){
  struct assignedNumber* res = (struct assignedNumber*)malloc(sizeof(struct assignedNumber));
  res->owner = p;
  res->number = n;
  return res;
}
