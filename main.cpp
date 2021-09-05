#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define TOWN_H
#define STACK_H
#define STACK_SIZE 1024


//town
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
//town function
struct town* createTown();

void enqueueApplication(struct town * t, struct application* a);

bool applicationsAvailable(struct town* t);

void processApplication(struct town * t);

void destroyApplication(struct application* a);

void destroyPerson(struct person* p);

void destroyTown(struct town* t);

void removeNumber(struct town* t, int number);

struct assignedNumber* assignNumber(struct person* p, int n);
//

//stract
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

#include "queue.h"

struct application* getApplication(){
  struct application* a = (struct application*)malloc(sizeof(struct application));
  struct person* p = (struct person*)malloc(sizeof(struct person));

  size_t bufferSize = 128;
  char* buffer = (char*)malloc(bufferSize * sizeof(char));
  printf("Enter name:");
  scanf("%[^\n]", buffer);
  getchar();

  //Copy name to person
  p->name = (char*)malloc(strlen(buffer)+1);
  strcpy(p->name, buffer);

  printf("Enter address:");
  scanf("%[^\n]", buffer);
  getchar();

  //Copy address to person
  p->address = (char*)malloc(strlen(buffer)+1);
  strcpy(p->address, buffer);

  a->person = p;

  printf("Enter date:");
  scanf("%[^\n]", buffer);
  getchar();

  //Copy date to application
  a->date = (char*)malloc(strlen(buffer)+1);
  strcpy(a->date, buffer);

  free(buffer);
  return a;
}

int main(){
  struct town* t = createTown();
  while(true){
    printf("\nSelect action:\n");
    printf(" e - enqueue a new application.\n");
    printf(" p - process application.\n");
    printf(" r - remove a telephone.\n");
    printf(" q - exit.\n");
    char c;
    scanf("%c",&c);
    getchar();
    if(c == 'e'){
      if(!isQueueFull(t->applications)){
        struct application* a = getApplication();
        enqueueApplication(t, a);
      } else {
        printf("Can't enqueue, queue is full.\n");
      }
    } else if(c == 'p'){
      if(applicationsAvailable(t)){
        processApplication(t);
      } else {
        printf("No applications to be processed.\n");
      }
    } else if(c == 'r'){
      printf("Select number to be removed: ");
      int number;
      scanf("%d", &number);
      getchar();
      removeNumber(t, number);
    } else if(c == 'q'){
      break;
    }
  }
  destroyTown(t);
}

//town function
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

//stack

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
