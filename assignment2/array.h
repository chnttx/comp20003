#ifndef _ARRAY_H_
#define _ARRAY_H_
#include "data.h"

#define INIT_SIZE 2

typedef struct array array_t;

array_t *arrayCreate();

void arrayFree(array_t *);

void arrayShrink(array_t *);

void arrayEnableInsert(array_t *);

void insertSortedArray(array_t *, restaurant_t *);

restaurant_t *binarySearch(array_t *arr, char *);

#endif