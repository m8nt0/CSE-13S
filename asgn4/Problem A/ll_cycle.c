#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    // have a slow and fast pointers at the start of head
    node *slow_ptr = head;
    node *fast_ptr = head;

    // have the fast ptr move ahead by two steps to see if it overlaps with slow ptr and it does then it cycles
    while (fast_ptr != NULL && fast_ptr->next != NULL) {
        // one step
        slow_ptr = slow_ptr->next;

        // two steps
        fast_ptr = fast_ptr->next->next;

        if (slow_ptr == fast_ptr) {
        // there exists a cycle
            return 1; 
        }
    }

    // no cycle exists.
    return 0;
}

