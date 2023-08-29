#ifndef _ARRAY_H_
#define _ARRAY_H_
#include "data.h"

#define INIT_SIZE 2

typedef struct array array_t;

array_t *arrayCreate();

int getSize(array_t *);

void arrayFree(array_t *);

void arrayShrink(array_t *);

void arrayEnableInsert(array_t *);

void insertSortedArray(array_t *, restaurant_t *);

void binarySearch(array_t *, int, char *, FILE *, int *, int *, int *);

void printArray(array_t *);
#endif