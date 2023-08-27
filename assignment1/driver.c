#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "data.h"
#include "lists.h"

list_t *buildRestaurantList(char *);
void listQuerying(char *, FILE *, FILE *);

int main(int argc, char **argv) {
    FILE *outFile = fopen(argv[3], "w");
    listQuerying(argv[2], outFile, stdin);
    fclose(outFile);
    return 0;
}

list_t *buildRestaurantList(char *filename) {
    FILE *f = fopen(filename, "r");
    assert(f);
    list_t *restaurants = listCreate();
    skipHeader(f);
    restaurant_t *res;
    while ((res = readRestaurant(f))) {
        listAppend(restaurants, res);
    }
    fclose(f);
    return restaurants;
}


void listQuerying(char *dataFilename, FILE *outFile, FILE *queryfile) {

    list_t *restaurants = buildRestaurantList(dataFilename);
    int count;
    char *searchQuery = NULL;

    size_t bufferSize = 0;
    __ssize_t charactersRead;

    while ((charactersRead = getline(&searchQuery, &bufferSize, queryfile)) != -1) {
        if (searchQuery[charactersRead - 1] == '\n') {
            searchQuery[charactersRead - 1] = '\0';
        }
        fprintf(outFile, "%s\n", searchQuery);
        count = findRestaurant(restaurants, searchQuery, outFile);
        printf("%s --> ", searchQuery);
        if (count) printf("%d\n", count);
        else printf("NOTFOUND\n");
    }
    freeList(restaurants);
    free(searchQuery);
}
