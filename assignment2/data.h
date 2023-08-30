#ifndef _DATA_H_
#define _DATA_H_

// define restaurant_t fields
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

// define compareBCS fields
#define STRINGS 0
#define CHARS 1
#define BITS 2
#define CHAR_BITS 8

typedef struct restaurant restaurant_t;

typedef int compareBCS[3];

void skipHeader(FILE *f);

restaurant_t *readRestaurant(FILE *f);

char *getName(void *);

void restaurantFree(void *);

void printRestaurant(restaurant_t *, FILE *);

void printRes(void *);

void assignRole(restaurant_t *, char *, int *);

int stringcmp(char *s1, char *s2, compareBCS);
#endif