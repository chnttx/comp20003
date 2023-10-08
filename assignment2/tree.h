#ifndef TREE_H
#define TREE_H
#include "data.h"
#include "array.h"
#define MAX_NAME_LEN 128
#define CHAR_BITS 8
#define BUFFER_SIZE 1033

typedef struct node node_t;
struct node {
    array_t *dataList;
    char *commonPrefix;
    node_t *left, *right;
};

node_t *insert(node_t *, char *, restaurant_t *);

void splitStem(char *, char *, char *);

node_t *newNode(char *);

char *stringToBinary(char *, int x);

node_t *searchTree(node_t *, char *, compareBCS, FILE *);

restaurant_t *getRestaurantAtIdx(array_t *, int);

void printTree(node_t *, FILE *);

array_t *getDataList(node_t *);

void freeTree(node_t *node);

void freeNode(node_t *node);
#endif