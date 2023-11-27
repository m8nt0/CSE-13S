#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "set.h"
#include "hashtable.h"
#include "lru.h"

// the sturct for the double link
typedef struct LRUCache_Node {
    char *key;
    void *item;
    struct LRUCache_Node *prev_node, *next_node;
} LRUCache_Node;

// the parrent of the double linked list above with more manipulation variables included
struct lru {
    int capacity;
    int num_size;
    LRUCache_Node *cache_head, *cache_tail;
    hashtable_t *hashtable_;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// a function to create a new Least used (LRU) cache
lru_t *lru_new(const int capacity) {
    lru_t *to_generate_lru = (lru_t *)malloc(sizeof(lru_t));
    if (to_generate_lru == NULL) {
        return NULL;
    }

    to_generate_lru->capacity = capacity;
    to_generate_lru->num_size = 0;
    to_generate_lru->cache_head = NULL;
    to_generate_lru->cache_tail = NULL;

    // using what we provided above to create a finite of buckets for lru hashtable
    to_generate_lru->hashtable_ = hashtable_new(capacity);
    if (to_generate_lru->hashtable_ == NULL) {
        free(to_generate_lru);
        return NULL;
    }

    return to_generate_lru;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// the delete a key coming from the lru_evict using a set_delete to kick out a key-item pair
void hashtable_delete_key(hashtable_t *ht, const char *key) {
    if (ht == NULL || key == NULL) {
        return;
    }

    unsigned int position = hashtable_hash(key, ht->num_slots); //using the hashtable_hash to determine the index of the key

    if (ht->buckets[position] != NULL) {
        set_delete(ht->buckets[position], NULL); // using set_delete and having NULL to not assoicate with delRecord only available in the other test cases
    }
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// coming from lru_insert to have the least key-pair from the hashtable
void lru_evict(lru_t *lru) {
    if (lru == NULL || lru->num_size == 0) {
        return;
    }

    // remove the tail node
    LRUCache_Node *sub = lru->cache_tail;
    lru->cache_tail = lru->cache_tail->prev_node;
    if (lru->cache_tail != NULL) {
        lru->cache_tail->next_node = NULL;
    }
    

    
    // using hashtable_delete_key from hashtable consequently using set_delete from set.c
    if (sub != NULL && sub->key != NULL) {
        hashtable_delete_key(lru->hashtable_, sub->key);
        //hashtable_delete(lru->hashtable_, NULL);
    }
    


    
    //free(sub->key);
    
    //free(sub->item);
    //free(sub);
    lru->num_size--;
    

}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Insert
bool lru_insert(lru_t *lru, const char *key, void *item) {
    if (lru == NULL || key == NULL || item == NULL) {
        return false;// if it is NULL
    }

    // to see if it existist (key) and leave false
    void *existing_item = hashtable_find(lru->hashtable_, key);
    //void *existing_item = lru_find(lru, key);
    if (existing_item != NULL) {
        // duplicate keys
        return false;
    }

    // if not we don't find it in the hashtable then we allocate
    LRUCache_Node *to_generate_node = (LRUCache_Node *)malloc(sizeof(LRUCache_Node));
    if (to_generate_node == NULL) {
        return false;
    }
    
    //dump the key and item and make the prev and next NULL
    to_generate_node->key = strdup(key);
    to_generate_node->item = item;
    to_generate_node->prev_node = NULL;
    to_generate_node->next_node = NULL;

    //putting the node as teh head and tail
    if (lru->cache_head == NULL) {
        lru->cache_head = to_generate_node;
        lru->cache_tail = to_generate_node;
    } else {//going from right to left and having the tail on the right
        to_generate_node->next_node = lru->cache_head;
        lru->cache_head->prev_node = to_generate_node;
        lru->cache_head = to_generate_node;
    }

    //after all this we actuall put this in the hashtable
    hashtable_insert(lru->hashtable_, key, item);
    lru->num_size++;//increment it to see it surpoassed the capcity
    
    

    // if it surpassed we go to evict mode: activated!!!
    if (lru->num_size > lru->capacity) {
        lru_evict(lru);
    }

    return true;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// to find the item in the cache using hashtable and moving through the LRU
void *lru_find(lru_t *lru, const char *key) {
    if (lru == NULL || key == NULL) {
        return NULL;
    }

    // using hashtable_find to find the item of the key
    void *item = hashtable_find(lru->hashtable_, key);
    if (item != NULL) {
        // trying to get the head
        LRUCache_Node *object = lru->cache_head; 

        // Traverse the list to find the node corresponding to the key
        while (object != NULL && strcmp(object->key, key) != 0) {
            object = object->next_node;
        }

        if (object != NULL) {
            // take out the node from the node list
            if (object->prev_node != NULL) {
                object->prev_node->next_node = object->next_node;
            }
            if (object->next_node != NULL) {
                object->next_node->prev_node = object->prev_node;
            }

            // Update 
            object->next_node = lru->cache_head;
            object->prev_node = NULL;

            if (lru->cache_head != NULL) {
                lru->cache_head->prev_node = object;
            }

            lru->cache_head = object;
        }
    }

    return item;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// to print to the an outside function
void lru_print(lru_t *lru, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)) {
    if (lru == NULL || fp == NULL || itemprint == NULL) {
        return;
    }

    // to go through and print each key-item pair
    LRUCache_Node *in_use = lru->cache_head;
    while (in_use != NULL) {
        (*itemprint)(fp, in_use->key, in_use->item);
        in_use = in_use->next_node;
    }
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// basically doing the same thing but a little different
void lru_iterate(lru_t *lru, void *arg, void (*itemfunc)(void *arg, const char *key, void *item)) {
    if (lru == NULL || itemfunc == NULL) {
        return;
    }

    // iterating and printing into a different file but looking the same
    LRUCache_Node *in_use = lru->cache_head;
    while (in_use != NULL) {
        (*itemfunc)(arg, in_use->key, in_use->item);
        in_use = in_use->next_node;
    }
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// to delete the LRU
void lru_delete(lru_t *lru, void (*itemdelete)(void *item)) {
    if (lru == NULL) {
        return;
    }
    

    // doing the deletion of the node
    LRUCache_Node *in_use = lru->cache_head;
    while (in_use != NULL) {
        LRUCache_Node *sub = in_use;
        in_use = in_use->next_node;
        
        if (itemdelete != NULL) {
            (*itemdelete)(sub->item);
        }
        
       
        //free(sub->key);
        //free(sub);
    }

    // doing the deletion of the hashtable
    if (lru->hashtable_ != NULL) {
        hashtable_delete(lru->hashtable_, NULL);
    }
    


    // deallocation
    free(lru);
}

