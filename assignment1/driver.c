#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "data.h"
#include "lists.h"

list_t *buildRestaurantList(char *);

int main(int argc, char **argv) {

    FILE *infoFile = fopen(argv[2], "w");
    assert(infoFile);

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

