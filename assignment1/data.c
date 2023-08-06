#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "data.h"

struct restaurant {
    int census_year, block_id, property_id, base_property_id, industry_code, num_seats;
    double longitude, latitude;
    char *bld_add, *clue_small_area, *business_add, *trading_name, *description, *seating;
};