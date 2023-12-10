#include <stdio.h>
#include <stdlib.h>
#include "crawler.h" // Assuming crawler.h defines webpage_t

// Structure to represent a bag of web pages_hold


// Function to create a new bag
bag_t *bag_to_create(size_t limit) {
    bag_t *bag = malloc(sizeof(bag_t));
    if (bag == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    bag->pages_hold = malloc(limit * sizeof(webpage_t *));
    if (bag->pages_hold == NULL) {
        perror("Memory allocation failed");
        free(bag);
        return NULL;
    }

    bag->limit = limit;
    bag->range = 0;

    return bag;
}

// Function to check if the bag is empty
bool is_bag_empty(const bag_t *bag) {
    return (bag == NULL || bag->range == 0);
}

// Function to insert a webpage into the bag
bool bag_insert(bag_t *bag, webpage_t *page) {
    if (bag == NULL || page == NULL || bag->range >= bag->limit) {
        return false;
    }

    bag->pages_hold[bag->range] = page; // Add 'page' to the pages_hold array at index 'range'
    bag->range++; // Increment the range counter after adding the page

    return true;
}

// Function to extract a webpage from the bag (FIFO)
webpage_t *bag_extract(bag_t *bag) {
    if (bag == NULL || bag->range == 0) {
        return NULL;
    }

    webpage_t *page = bag->pages_hold[0]; // Get the first webpage from the pages_hold array

    // Shift all elements to the left to maintain FIFO behavior
    for (size_t i = 0; i < bag->range - 1; ++i) {
        bag->pages_hold[i] = bag->pages_hold[i + 1];
    }

    bag->range--; // Decrement range after extraction

    return page;
}

// Function to destroy the bag
void bag_destroy(bag_t *bag) {
    if (bag == NULL) {
        return;
    }

    free(bag->pages_hold);
    free(bag);
}

