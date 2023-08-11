#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "data.h"

char *getName(restaurant_t restaurant) {
    return restaurant.trading_name;
}

