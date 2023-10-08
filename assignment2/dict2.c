#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
// #include <time.h>
#include "array.h"
#include "data.h"

void arrayQuerying(int *, char *, FILE *, FILE*, int *, int *);
array_t *buildArray(char *);

int main(int argc, char **argv){
    // clock_t begin = clock();
    FILE *outFile = fopen(argv[3], "w");
    int cmp = 0, total = 0, x = 0;
    arrayQuerying(&x, argv[2], outFile, stdin, &cmp, &total);
    fclose(outFile);
    printf("%lf\n", (double) cmp / total);
    printf("%d\n", x);
    // clock_t end = clock();
    // printf("%lf\n", (double)(end - begin) / CLOCKS_PER_SEC);
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


void arrayQuerying(int *x1, char *dataFilename, FILE *outFile, FILE *queryfile, int *x, int *y) {

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
        *x += currCmp[STRINGS];
        *y += 1;
    }

    arrayFree(restaurants);
    free(query);
}