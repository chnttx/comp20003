#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "data.h"
#include "array.h"

struct restaurant {
    int census_year, block_id, property_id, base_property_id, industry_code, num_seats;
    double longitude, latitude;
    char *bld_add, *clue_small_area, *business_add, *trading_name, *description, *seating;
};

char *getName(void *res) {
    return ((restaurant_t *)res)->trading_name;
}

void skipHeader(FILE *f) {
    while (fgetc(f) != '\n');
}

restaurant_t *readRestaurant(FILE *f) {
    restaurant_t *res = NULL;
    char *line = NULL;
    size_t len;

    if (getline(&line, &len, f) != -1) {
        res = malloc(sizeof(*res));
        assert(res);
        int count = 1, buf = 0, fieldIdx = 0;
        char field[MAX_FIELD_LEN + 1];
        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] == '"') {
                if (line[i + 1] == ',') {
                    field[fieldIdx] = '\0';
                    assignRole(res, field, &count);
                    buf = 0;
                    fieldIdx = 0;
                    field[fieldIdx] = '\0';
                } else if (line[i - 1] == ',') {
                    buf = 1;
                }
            } else if (line[i] == ',' && !buf) {
                field[fieldIdx] = '\0';
                if (field[0] != '\0') {
                    assignRole(res, field, &count);
                } fieldIdx = 0;
            } else {
                field[fieldIdx++] = line[i];
            }
        } assignRole(res, field, &count);
    }
    free(line);
    return res;
}

void assignRole(restaurant_t *res, char *word, int *count) {
    switch (*count) {
        case CENSUS_YEAR:
            res->census_year = atoi(word);
            (*count)++;
            break;
        case BLOCK_ID:
            res->block_id = atoi(word);
            (*count)++;
            break;
        case PROPERTY_ID:
            res->property_id = atoi(word);
            (*count)++;
            break;
        case BASE_PROPERTY_ID:
            res->base_property_id = atoi(word);
            (*count)++;
            break;
        case BUILDING_ADDRESS:
            res->bld_add = strdup(word);
            assert(res->bld_add);
            (*count)++;
            break;
        case CLUE_SMALL_AREA:
            res->clue_small_area = strdup(word);
            assert(res->clue_small_area);
            (*count)++;
            break;
        case BUSINESS_ADDRESS:
            res->business_add = strdup(word);
            assert(res->business_add);
            (*count)++;
            break;
        case TRADING_NAME:
            res->trading_name = strdup(word);
            assert(res->trading_name);
            (*count)++;
            break;
        case INDUSTRY_CODE:
            res->industry_code = atoi(word);
            (*count)++;
            break;
        case DESCRIPTION:
            res->description = strdup(word);
            assert(res->description);
            (*count)++;
            break;
        case SEATING_TYPE:
            res->seating = strdup(word);
            assert(res->seating);
            (*count)++;
            break;
        case SEAT_NUMBERS:
            res->num_seats = atoi(word);
            (*count)++;
            break;
        case LONGITUDE:
            res->longitude = atof(word);
            (*count)++;
            break;
        case LATITUDE:
            res->latitude = atof(word);
            (*count)++;
            break;
        default: return;
    } 
}

void printRestaurant(restaurant_t *res, FILE *outFile) {
    fprintf(outFile, "--> census_year: %d ||", res->census_year);
    fprintf(outFile, " block_id: %d ||", res->block_id);
    fprintf(outFile, " property_id: %d ||", res->property_id);
    fprintf(outFile, " base_property_id: %d ||", res->base_property_id);
    fprintf(outFile, " building_address: %s ||", res->bld_add);
    fprintf(outFile, " clue_small_area: %s ||", res->clue_small_area);
    fprintf(outFile, " business_address: %s ||", res->business_add);
    fprintf(outFile, " trading_name: %s ||", res->trading_name);
    fprintf(outFile, " industry_code: %d ||", res->industry_code);
    fprintf(outFile, " industry_description: %s ||", res->description);
    fprintf(outFile, " seating_type: %s ||", res->seating);
    fprintf(outFile, " number_of_seats: %d ||", res->num_seats);
    fprintf(outFile, " longtitude: %.5lf ||", res->longitude);
    fprintf(outFile, " latitude: %.5lf ||\n", res->latitude);
}

void restaurantFree(void *res) {
    free(((restaurant_t *)res)->bld_add);
    free(((restaurant_t *)res)->clue_small_area);
    free(((restaurant_t *)res)->business_add);
    free(((restaurant_t *)res)->trading_name);
    free(((restaurant_t *)res)->description);
    free(((restaurant_t *)res)->seating);
    free(res);
}

void printRes(void *res) {
    printf("%d\n", ((restaurant_t *)res)->census_year);
    printf("%d\n", ((restaurant_t *)res)->block_id);
    printf("%d\n", ((restaurant_t *)res)->property_id);
    printf("%d\n", ((restaurant_t *)res)->base_property_id);
    printf("%s\n", ((restaurant_t *)res)->bld_add);
    printf("%s\n", ((restaurant_t *)res)->clue_small_area);
    printf("%s\n", ((restaurant_t *)res)->business_add);
    printf("%s\n", ((restaurant_t *)res)->trading_name);
    printf("%d\n", ((restaurant_t *)res)->industry_code);
    printf("%s\n", ((restaurant_t *)res)->description);
    printf("%s\n", ((restaurant_t *)res)->seating);
    printf("%d\n", ((restaurant_t *)res)->num_seats);
    printf("%lf\n", ((restaurant_t *)res)->longitude);
    printf("%lf\n\n", ((restaurant_t *)res)->latitude);
}

int stringcmp(char *s1, char *s2) {
    int i;
    for (i = 0; s1[i] && s2[i] && s1[i] == s2[i]; i++);
    return i + 1;
}