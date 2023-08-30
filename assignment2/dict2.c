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
    int arrSize = getSize(restaurants);
    char *query = NULL;
    size_t bufferSize = 0, read;

    while ((read = getline(&query, &bufferSize, queryfile)) != -1) {
        if (query[read - 1] == '\n') {
            query[read - 1] = '\0';
        }
        compareBCS currCmp = {0, 0, 0};

        fprintf(outFile, "%s\n", query);
        search(restaurants, arrSize, query, outFile, currCmp);
        printf("%s --> b%d c%d s%d\n", query, currCmp[BITS], currCmp[CHARS], currCmp[STRINGS]);
    }

    arrayFree(restaurants);
    free(query);
}