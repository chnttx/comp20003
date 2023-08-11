#ifndef _LISTS_H_
#define _LISTS_H_
#include "data.h"
typedef struct list list_t;



list_t *listCreate();

void listFree();

void listAppend(list_t *, restaurant_t);

int findRestaurant(list_t *, char *);


#endif