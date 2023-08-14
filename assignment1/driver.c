#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "data.h"
#include "lists.h"

list_t *buildRestaurantList(char *);
void listQuerying();

int main(int argc, char **argv) {

    FILE *infoFile = fopen(argv[3], "w");
    assert(infoFile);

    listQuerying(argv[2], stdin, stdout, infoFile);

    fclose(infoFile);

    return 0;

}

list_t *buildRestaurantList(char* filename) {
    FILE *f = fopen(filename, "r");
    assert(f);

    list_t *restaurants = listCreate();
    skipHeader(f);
    restaurant_t *res;

    while ((res = getRestaurant(f))) {
        listAppend(restaurants, res);
    }

    fclose(f);
    return restaurants;
}

void listQuerying(char *dataFilename, FILE *inFile, FILE *outFile, FILE *infoFile) {

    list_t *restaurants = buildRestaurantList(dataFilename);

    char *searchQuery;
    restaurant_t *r;

    size_t bufferSize = 0;
    __ssize_t charactersRead;

    while ((charactersRead = getline(&searchQuery, &bufferSize, stdin)) != -1) {
        if (searchQuery[charactersRead - 1] == '\n') {
            searchQuery[charactersRead - 1] = '\0';
        }

        printf("%s\n%ld\n", searchQuery, strlen(searchQuery));
    }
    free(searchQuery);

}