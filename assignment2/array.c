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
    for (i = arr->currCount - 1; i >= 0 && strcmp(getName(arr->A[i]), getName(res)) >= 0; i--) {
        arr->A[i + 1] = arr->A[i];
    }
    arr->A[i + 1] = res;
    (arr->currCount)++;
}

void search(array_t *arr, int size, char *key, FILE *outFile, compareBCS cmp) {
    restaurant_t **restaurants = arr->A;
    int mid, outcome, lo = 0, hi = arr->currCount - 1;
    char *currName = NULL;
    
    // binary search
    while (lo <= hi) {
        mid = lo + (hi - lo) / 2;
        currName = getName(restaurants[mid]);
        outcome = stringcmp(currName, key, cmp);
        
        if (!outcome) {
            printRestaurant(restaurants[mid], outFile);
            break;
        } else if (outcome < 0) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    // linear search in the surrounding indices
    for (int i = mid - 1; i >= 0; i--) {
        if (stringcmp(getName(restaurants[i]), key, cmp)) break;
        printRestaurant(restaurants[i], outFile);
    } for (int j = mid + 1; j < arr->currCount; j++) {
        if (stringcmp(getName(restaurants[j]), key, cmp)) break;
        printRestaurant(restaurants[j], outFile);
    }
}