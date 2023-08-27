#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "lists.h"
#include "data.h"

typedef struct node node_t;
struct node {
    restaurant_t *data;
    node_t *next;
};

struct list{
    // points to the first and last node in the list
    node_t *head, *tail;
    // number of elements in list
    size_t n; 
};

list_t *listCreate() {
    list_t *list = malloc(sizeof(*list));
    assert(list);
    list->head = list->tail = NULL;
    list->n = 0;
    return list;
}

void listAppend(list_t *list, void *newData) {
    node_t *new = malloc(sizeof(*new));
    assert(new);
    new->data = newData;
    new->next = NULL;
    if (list->head == NULL) {
        list->head = list->tail = new;
    } else {
        list->tail->next = new;
        list->tail = new;
    } (list->n)++;
}



int findRestaurant(list_t *list, char *name, FILE *outFile) {
    node_t *curr = list->head;
    char *word;
    int count = 0;

    while (curr) {
        word = getName(curr->data);
        if (!strcmp(word, name)) {
            count++;
            printRestaurant(curr->data, outFile);
        } curr = curr->next;
    }

    return count;
}

void freeList(list_t *list) {
    assert(list != NULL);
    node_t *curr = list->head;
    while (curr) {
        node_t *tmp = curr;
        curr = curr->next;
        restaurantFree(tmp->data);
        free(tmp);
    } free(list);
}