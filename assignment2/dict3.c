#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "data.h"
#include "array.h"
#include "tree.h"

node_t *buildTree(char *);
void treeQuerying(char *, FILE *, FILE *);

int main(int argc, char **argv) {
    if (argc < 4) {
        printf("Not enough arguments. Program will exit.\n");
        exit(EXIT_FAILURE);
    }
    FILE *outFile = fopen(argv[3], "w");
    assert(outFile);
    treeQuerying(argv[2], outFile, stdin);
    fclose(outFile);
    return 0;
}

node_t *buildTree(char *filename) {
    FILE *f = fopen(filename, "r");
    assert(f);
    node_t *tree = NULL;
    skipHeader(f);
    restaurant_t *res;
    while ((res = readRestaurant(f))) {
        char *name = stringToBinary(getName(res), 1); 
        tree = insert(tree, name, res);
        free(name);
    }
    fclose(f);
    return tree;
}

void treeQuerying(char *dataFilename, FILE *outFile, FILE *queryfile) {
    node_t *restaurants = buildTree(dataFilename);
    char *query = NULL;
    size_t bufferSize = 0, read;

    while ((read = getline(&query, &bufferSize, queryfile)) != -1) {
        if (query[read - 1] == '\n') query[read - 1] = '\0';
        char *key = stringToBinary(query, 1);
        compareBCS currCmp = {0, 0, 0};

        fprintf(outFile, "%s\n", query);
        node_t *result = searchTree(restaurants, key, currCmp, outFile);
        if (result);
        // if (result == NULL) printf("1");
        printf("%s --> b%d c%d s1\n", query, currCmp[BITS], currCmp[CHARS]);
        free(key);
    }
    free(query);
    freeTree(restaurants);
}



