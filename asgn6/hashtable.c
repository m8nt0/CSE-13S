#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

unsigned int hashtable_hash(const char *key, const int num_slots) {
    unsigned int the_hash = 0;
    int initial = 0;
    while (key[initial] != '\0') {
        the_hash = (the_hash << 5) + key[initial]; // shift the_hash by 32 bits to the left meaning multiply the_hash by 32 and add the key (each alphabet)
        ++initial;
    }
    return the_hash % num_slots; //using modulous to determine the the_position
}

hashtable_t *hashtable_new(const int num_slots) {
    hashtable_t *generate_new_ht = (hashtable_t *)malloc(sizeof(hashtable_t));
    if (generate_new_ht != NULL) {
        generate_new_ht->num_slots = num_slots;
        
        generate_new_ht->buckets = (set_t **)malloc(num_slots * sizeof(set_t *)); // simple allocation of buckets
        if (generate_new_ht->buckets == NULL) {
            //free(generate_new_ht->buckets);
            free(generate_new_ht);
            return NULL;// If it fails
        }

        for (int i = 0; i < num_slots; ++i) {
            generate_new_ht->buckets[i] = set_new(); //set_new for each buckets within the hashtable
            if (generate_new_ht->buckets[i] == NULL) { //if it fails
                for (int j = 0; j < i; ++j) {
                    set_delete(generate_new_ht->buckets[j], NULL);
                }
                free(generate_new_ht->buckets);//deallocation
                free(generate_new_ht);
                return NULL;
            }
        }
    }
    return generate_new_ht;
}

bool hashtable_insert(hashtable_t *ht, const char *key, void *item) {
    if (ht == NULL || key == NULL || item == NULL) {
        return false; //if they happen to be Null
    }

    int the_position = hashtable_hash(key, ht->num_slots); //Using the hashtable_hash to determine the the_position
    if (set_insert(ht->buckets[the_position], key, item)) { //Using the set_insert from set.c to put the key-item pair in the calculated the_position of the buckets
        return true;
    }
    
    return false;
}

//Basically a function to find the item of the key by using the comnbiation of hash function to find the the_position and set_find to determine the item of the key
void *hashtable_find(hashtable_t *ht, const char *key) {
    if (ht == NULL || key == NULL) {
        return NULL;
    }

    int the_position = hashtable_hash(key, ht->num_slots);
    return set_find(ht->buckets[the_position], key);
}

//using set_print to print each of the the_position of the buckets of the hashtable
void hashtable_print(hashtable_t *ht, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)) {
    if (ht == NULL || fp == NULL || itemprint == NULL) {
        return; // if false
    }

    for (int i = 0; i < ht->num_slots; ++i) {
        if (ht->buckets[i] != NULL) {
            set_print(ht->buckets[i], fp, itemprint);
        }
    }
}

// Using set_iterate to do the same as set_print
void hashtable_iterate(hashtable_t *ht, void *arg, void (*itemfunc)(void *arg, const char *key, void *item)) {
    if (ht == NULL || itemfunc == NULL) {
        return;
    }

    for (int i = 0; i < ht->num_slots; ++i) {
        if (ht->buckets[i] != NULL) {
            set_iterate(ht->buckets[i], arg, itemfunc);
        }
    }
}

//the whole hashtable to be deleted
void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item)) {
    if (ht == NULL) {
        return;
    }

    //for (int i = 0; i < ht->num_slots; ++i) {
        //if (ht->buckets[i] != NULL) {
            //set_delete(ht->buckets[i], itemdelete);
        //}
    //}
    
    if (itemdelete != NULL) {
        for (int i = 0; i < ht->num_slots; ++i) {
             if (ht->buckets[i] != NULL) {
                 set_delete(ht->buckets[i], itemdelete);
             }
        }
    } else {
        for (int i = 0; i < ht->num_slots; ++i) {
             if (ht->buckets[i] != NULL) {
                 //i think it is here
                 //printf("i think it is here\n");
                 set_delete(ht->buckets[i], NULL);
             }
        }
    }   
    //free(ht->generate_new_ht);
    free(ht->buckets);// free the allocated hashtable as well as each buckets
    free(ht);
}

