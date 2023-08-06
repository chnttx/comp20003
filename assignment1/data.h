#ifndef _DATA_H_
#define _DATA_H_

// Defining constants
#define MAX_FIELD_LEN 128

// Data definitions
struct restaurant {
    int census_year, block_id, property_id, base_property_id, industry_code, num_seats;
    double longitude, latitude;
    char bldg_addr[MAX_FIELD_LEN + 1], clue_small_area[MAX_FIELD_LEN + 1], business_addr[MAX_FIELD_LEN + 1];
    char name[MAX_FIELD_LEN + 1], description[MAX_FIELD_LEN + 1], seating_type[MAX_FIELD_LEN + 1];
};

typedef struct restaurant restaurant_t;

#endif