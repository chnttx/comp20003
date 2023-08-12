#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc < 4) {
        exit(EXIT_FAILURE);
    }

    FILE *inFile = fopen(argv[2], "r"), *outFile = fopen(argv[3], "w");
    assert(inFile && outFile);

    
}