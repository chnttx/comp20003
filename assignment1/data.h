#ifndef _DATA_H_
#define _DATA_H_
#include <stdio.h>
// Defining constants

#define MAX_FIELD_LEN 128
#define CENSUS_YEAR 1
#define BLOCK_ID 2
#define PROPERTY_ID 3
#define BASE_PROPERTY_ID 4
#define BUILDING_ADDRESS 5
#define CLUE_SMALL_AREA 6
#define BUSINESS_ADDRESS 7
#define TRADING_NAME 8
#define INDUSTRY_CODE 9
#define DESCRIPTION 10
#define SEATING_TYPE 11
#define SEAT_NUMBERS 12
#define LONGITUDE 13
#define LATITUDE 14

// Data definitions
struct restaurant {
    int census_year, block_id, property_id, base_property_id, industry_code, num_seats;
    double longitude, latitude;
    char *bld_add, *clue_small_area, *business_add, *trading_name, *description, *seating;
};

typedef struct restaurant restaurant_t;

void skipHeader(FILE *f);

restaurant_t *readRestaurant(FILE *f);

char *getName(void *);

void restaurantFree(void *);

void printRestaurant(restaurant_t *, FILE *);

void printRes(restaurant_t *);

void assignRole(restaurant_t *, char *, int *);
#endif