#ifndef ARRAY_H
#define ARRAY_H
#include "data.h"

#define INIT_SIZE 2

typedef struct array array_t;

array_t *arrayCreate();

int getSize(array_t *);

void arrayFree(array_t *);

void arrayShrink(array_t *);

void arrayEnableInsert(array_t *);

void insertSortedArray(array_t *, restaurant_t *);

void search(array_t *, int, char *, FILE *, compareBCS);

void printArray(array_t *, FILE *);
#endif