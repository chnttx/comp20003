#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "array.h"
#include "data.h"

struct array {
    restaurant_t **A;
    int size, currCount;
};

array_t *arrayCreate() {
    array_t *arr = malloc(sizeof(*arr));
    assert(arr);
    int size = INIT_SIZE;
    arr->size = size;
    arr->A = malloc(size * sizeof(*(arr->A)));
    assert(arr->A);
    arr->currCount = 0;
    return arr; 
}

void arrayFree(array_t *arr) {
    for (int i = 0; i < arr->size; i++) {
        restaurantFree(arr->A[i]);
    }
    free(arr->A);
    free(arr);
}

void arrayEnableInsert(array_t *arr){
    if (arr->currCount == arr->size) {
        arr->size <<= 1;
        arr->A = realloc(arr->A, arr->size * sizeof(*(arr->A)));
        assert(arr->A);
    }
}

void arrayShrink(array_t *arr) {
    if (arr->size != arr->currCount) {
        arr->size = (arr->currCount > INIT_SIZE) ? arr->currCount : INIT_SIZE;
        arr->A = realloc(arr->A, arr->size * sizeof(*(arr->A)));
        assert(arr->A);
    }
}
void insertSortedArray(array_t *arr, restaurant_t *res) {
    int i;
    arrayEnableInsert(arr);
    for (i = arr->currCount - 1; i >= 0 && strcmp(getName(res), getName(arr->A[i])) == -1; i--) {
        arr->A[i + 1] = arr->A[i];
    }
    arr->A[i + 1] = res;
    (arr->currCount)++;
}