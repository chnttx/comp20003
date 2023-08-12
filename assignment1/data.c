#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "data.h"
#include "lists.h"
char *getName(restaurant_t restaurant) {
    return restaurant.trading_name;
}

void printCount(char* name, list_t *lst) {
    printf("%s --> %d\n", name, findRestaurant(lst, name));
}
