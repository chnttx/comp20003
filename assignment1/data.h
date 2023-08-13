#ifndef _DATA_H_
#define _DATA_H_
#include <stdio.h>
// Defining constants

// Data definitions
struct restaurant {
    int census_year, block_id, property_id, base_property_id, industry_code, num_seats;
    double longitude, latitude;
    char *bld_add, *clue_small_area, *business_add, *trading_name, *description, *seating;
};

typedef struct restaurant restaurant_t;

void skipHeader(FILE *f);

char *getName(restaurant_t *);

void restaurantFree(restaurant_t);

void printRestaurant(restaurant_t, char *);

#endif