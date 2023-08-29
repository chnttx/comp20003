#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "array.h"
#include "data.h"

void arrayQuerying(char *, FILE *, FILE*);
array_t *buildArray(char *);

int main(int argc, char **argv){
    FILE *outFile = fopen(argv[3], "w");
    arrayQuerying(argv[2], outFile, stdin);
    fclose(outFile);
    return 0;
}

array_t *buildArray(char *filename) {
    FILE *f = fopen(filename, "r");
    assert(f);
    array_t *restaurants = arrayCreate();
    skipHeader(f);
    restaurant_t *res;
    while ((res = readRestaurant(f))) {
        insertSortedArray(restaurants, res);
    }
    fclose(f);
    arrayShrink(restaurants);
    return restaurants;
}


void arrayQuerying(char *dataFilename, FILE *outFile, FILE *queryfile) {

    array_t *restaurants = buildArray(dataFilename);
    // printArray(restaurants);
    // printf("\n");
    int arrSize = getSize(restaurants);
    char *query = NULL;
    size_t bufferSize = 0, read;

    while ((read = getline(&query, &bufferSize, queryfile)) != -1) {
        if (query[read - 1] == '\n') {
            query[read - 1] = '\0';
        }
        int bits = 0, ch = 0, str = 0;
        // fprintf(outFile, "%s\n", query);
        binarySearch(restaurants, arrSize, query, outFile, &bits, &ch, &str);
        printf("%s --> b%d c%d s%d\n", query, bits, ch, str);
        // if (1) printf("%db %dc %ds\n", bytes, ch, str);
        // else printf("NOTFOUND\n");
    }
    arrayFree(restaurants);
    free(query);
}