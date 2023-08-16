#ifndef _LISTS_H_
#define _LISTS_H_

typedef struct list list_t;

list_t *listCreate();

void freeList(list_t *);

void listAppend(list_t *, void *);

int findRestaurant(list_t *, char *, FILE *);

void printCount(char *, list_t *);

#endif