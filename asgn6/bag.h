#ifndef BAG_H_
#define BAG_H_

// Structure for bag ADT
typedef struct bag bag_t;

// Function prototypes
bag_t *create_bag(int initial_capacity);
void bag_insert(bag_t *bag, void *item);
void *bag_extract(bag_t *bag);
bool bag_is_empty(bag_t *bag);
void destroy_bag(bag_t *bag);

#endif // BAG_H_

