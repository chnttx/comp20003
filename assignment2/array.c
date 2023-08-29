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

int getSize(array_t *arr) {
    return arr->currCount;
}

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
    for (int i = 0; i < arr->currCount; i++) {
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
    for (i = arr->currCount - 1; i >= 0 && strcmp(getName(arr->A[i]), getName(res)) > -1; i--) {
        arr->A[i + 1] = arr->A[i];
    }
    arr->A[i + 1] = res;
    (arr->currCount)++;
}

void binarySearch(array_t *arr, int size, char *key, FILE *outFile, int *bits, int *ch, int *s) {
    restaurant_t **a = arr->A;
    int mid, outcome, lo = 0, hi = arr->currCount - 1, comps = 0, n;
    char *curr = NULL;
    while (lo <= hi) {
        mid = lo + (hi - lo) / 2;
        curr = getName(a[mid]);
        outcome = strncmp(curr, key, strlen(key));

        if (outcome < 0) {
            lo = mid + 1;
        } else if (outcome > 0){
            hi = mid - 1;
        } else {
            comps++;
            (*s)++;
            n = stringcmp(curr, key);
            (*ch) += n;
            (*bits) += 8 * n;
            break;
        }
        comps++;
        (*s)++;
        n = stringcmp(curr, key);
        // printf("%d\n", n);
        (*ch) += n;
        (*bits) += 8 * n; 
    } 
    // printf("%d %d %d %d comps\n", *bits, *ch, *s, comps);
    // printf("mid = %d\n", mid);
    for (int i = mid - 1; i >= 0; i--) {
        (*s)++;
        n = stringcmp(getName(a[i]), key);
        (*ch) += n;
        (*bits) += 8 * n;
        if (strncmp(key, getName(a[i]), strlen(key))) {
            break;
        }
    }
    for (int j = mid + 1; j < arr->currCount; j++){
        (*s)++;
        n = stringcmp(getName(a[j]), key);
        (*ch) += n;
        (*bits) += 8 * n;
        if (strncmp(key, getName(a[j]), strlen(key))) {
            break;
        }
    }
}

void printArray(array_t *arr) {
    restaurant_t **a = arr->A;
    
    for (int i = 0 ; i < arr->currCount; i++) {
        printf("%d %s %ld\n", i, getName(a[i]), strlen(getName(a[i])) + 1);
    }
}