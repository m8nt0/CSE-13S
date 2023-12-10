#ifndef CRAWLER_H
#define CRAWLER_H

#include <stddef.h>
#include <stdbool.h>
//++++++++++
//#include "bag.h"

typedef struct {
    char *the_url;
    char *html;
    size_t length;
    int depth;
} webpage_t;

// Basic implementation of bag data structure using an array
typedef struct {
    webpage_t **pages_hold;
    size_t limit;
    size_t range;
} bag_t;

// Function prototypes for bag.c
bag_t *bag_to_create(size_t limit);
bool bag_insert(bag_t *bag, webpage_t *page);
bool is_bag_empty(const bag_t *bag);
webpage_t *bag_extract(bag_t *bag);
void bag_destroy(bag_t *bag);

#endif

