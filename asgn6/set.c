#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

// this creates new set
set_t* set_new(void) {
    set_t *generate_new_set = malloc(sizeof(set_t));
    if (generate_new_set != NULL) {
        generate_new_set->head = NULL;
        //To have it work we need to make the head of the new_set NULL
    }
    return generate_new_set;
}

// put and insert the key-item into the set
bool set_insert(set_t *set, const char *key, void *item) {
    if (set == NULL || key == NULL || item == NULL)
        return false;

    // this checks if the key already exists
    node_pointer *the_lead = set->head;
    while (the_lead != NULL) {
        if (strcmp(the_lead->key, key) == 0)
            return false; // if it reaches here it means it exists
        the_lead = the_lead->next;
    }
    
    
    // If it doesn't exist, it comes to this point in creating a node
    node_pointer *node_new = malloc(sizeof(node_pointer));
    if (node_new == NULL)
        return false; // this means the allocation of memory for some reason failed

    node_new->key = strdup(key); // a duplicate copy of the key passed in by running a malloc and strcpy; a mashup
    node_new->item = item;
    node_new->next = set->head;
    set->head = node_new;
    

    return true; // the item and key were inserted correctly
}

// To find the item of a key, a simple algorithm
void *set_find(set_t *set, const char *key) {
    if (set == NULL || key == NULL)
        return NULL;

    node_pointer *the_lead = set->head;
    while (the_lead != NULL) {
        if (strcmp(the_lead->key, key) == 0) //Does str compare to see if the next of the_lead each time equates the key
            return the_lead->item;
        the_lead = the_lead->next;
    }

    return NULL; // not succesful of finding the key in order to retierve the item
}

// To print to an outside txt
void set_print(set_t *set, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)) {
    if (set == NULL || fp == NULL)
        return;

    node_pointer *the_lead = set->head;
    while (the_lead != NULL) {
        (*itemprint)(fp, the_lead->key, the_lead->item); //a pointer referring to the function proided in the test_set
        the_lead = the_lead->next;
    }
}

// Does the same as the set_print except it does it in unordered fashion, and more generic
void set_iterate(set_t *set, void *arg, void (*itemfunc)(void *arg, const char *key, void *item)) {
    if (set == NULL || itemfunc == NULL)
        return;

    node_pointer *the_lead = set->head;
    while (the_lead != NULL) {
        (*itemfunc)(arg, the_lead->key, the_lead->item);
        the_lead = the_lead->next;
    }
}

// to completely delete the set
void set_delete(set_t *set, void (*itemdelete)(void *item)) {
    if (set == NULL)
        return;

    node_pointer *the_lead = set->head;
    while (the_lead != NULL) {
        node_pointer *bucket = the_lead;
        the_lead = the_lead->next;

        if (itemdelete != NULL)
            (*itemdelete)(bucket->item); // leads to the destructor

        free(bucket->key);
        free(bucket);
    }

    free(set);
}

