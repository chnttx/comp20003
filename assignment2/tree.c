#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "tree.h"
#include "data.h"
#include "array.h"

// #define MAX_NAME_LEN 128
// #define CHAR_BITS 8
#define BUFFER_SIZE 1033




void splitStem(char *s1, char *s2, char *result) {
  char *res = result;
  assert(res);
  while (*s1 && *s2 && *s1 == *s2) {
    *res++ = *s1;
    ++s1;
    ++s2;
  }
  *res = '\0';
}

node_t *newNode(char *bits) {
    node_t *res = malloc(sizeof(*res));
    assert(res);

    res->commonPrefix = bits ? strdup(bits) : NULL;
    res->left = res->right = NULL;
    res->dataList = arrayCreate();
    return res;
}

node_t *insert(node_t *root, char *bits, restaurant_t *res) {
    if (!root) {
        root = newNode(bits);
        insertSortedArray(root->dataList, res);
        return root;
    } else {
        restaurant_t *rootOldData[getSize(root->dataList)];
        for (int j = 0; j < getSize(root->dataList); j++) {
            rootOldData[j] = getRestaurantAtIdx(root->dataList, j);
        }
        insertSortedArray(root->dataList, res);
        char *rootBits = root->commonPrefix, *currBits = bits;
        
        while (*rootBits && *bits && *rootBits == *bits) {
            ++rootBits;
            ++bits;
        }

        if (!*rootBits && *bits) {
            if (*bits == '0') root->left = insert(root->left, bits, res);
            else root->right = insert(root->right, bits, res);
        }

        else if (*rootBits) {
            char newRoot[strlen(root->commonPrefix)];
            splitStem(root->commonPrefix, currBits, newRoot);
            root->commonPrefix = strdup(newRoot);
            // free(root->commonPrefix);

            node_t *currLeft = NULL, *currRight = NULL;

            if (root->left && root->right) {
                currLeft = root->left;
                currRight = root->right;
            } else if (root->right) currRight = root->right;
            else currLeft = root->left;

            node_t *newChild = newNode(rootBits);

            for (int idx = 0; idx < getSize(root->dataList) - 1; idx++) {
                insertSortedArray(newChild->dataList, rootOldData[idx]);
            }

            if (*rootBits == '0') {
                root->left = newChild;
                if (currLeft) newChild->left = currLeft;
                if (currRight) newChild->right = currRight;
                root->right = newNode(bits);
                insertSortedArray(root->right->dataList, res);
            } else {
                root->right = newChild;
                if (currLeft) newChild->left = currLeft;
                if (currRight) newChild->right = currRight;
                root->left = newNode(bits);
                insertSortedArray(root->left->dataList, res);
            }
        }
    }
    return root;
}

char* stringToBinary(char* s, int isNullByte) {
    size_t len = strlen(s) + isNullByte;
    char *binary = malloc(len * 8 + 1); // Each char is one byte (8 bits)
    assert(binary);
    binary[0] = '\0';

    for(size_t i = 0; i < len; ++i) {
        char ch = s[i];
        for(int j = 7; j >= 0; --j){
            if(ch & (1 << j)) {
                strcat(binary, "1");
            } else {
                strcat(binary, "0");
            }
        }
    }

    return binary;
}

node_t *searchTree(node_t *root, char *keyBits, compareBCS currCmp, FILE *outFile) {
    if (!root) {
        // printf("NOT FOUND");
        return NULL;
    } 
    char *rootBits = root->commonPrefix, *kBits = keyBits;
    while (*rootBits && *kBits && *rootBits == *kBits) {
        if ((kBits - keyBits) % 8 == 0) ++currCmp[CHARS];
        ++currCmp[BITS];
        ++rootBits;
        ++kBits;
    }

    if (*rootBits && *rootBits != *kBits) {
        // ++currCmp[BITS];
        printArray(root->dataList, outFile);
        return root;
    } else if (!*kBits) {
        printArray(root->dataList, outFile);
        return root;
    }
    else {
        if (*kBits == '0') return searchTree(root->left, kBits, currCmp, outFile);
        else return searchTree(root->right, kBits, currCmp, outFile);
    }
}

void printTree(node_t *root, FILE *outFile) {
    if (!root) return;
    // printf("%s\n", root->commonPrefix);
    printArray(root->dataList, outFile);
    // printTree(root->left);
    // printTree(root->right);
}

array_t *getDataList(node_t *root) {
    return root->dataList;
}

void freeTree(node_t *root) {
    if (root == NULL) return;
    if (root->left != NULL) freeTree(root->left);
    if (root->right != NULL) freeTree(root->right);
    free(root->commonPrefix);
    if (root->dataList) arrayFree(root->dataList);
    free(root);
}