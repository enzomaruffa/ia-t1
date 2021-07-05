#include <stdlib.h>
#include "frontier.h"

void clone_frontier_node(FrontierNode_t *dest, FrontierNode_t *original) {
    dest->x = original->x;
    dest->y = original->y;
    dest->directions_count = original->directions_count;
    
    dest->frontiers = malloc(sizeof(FrontierDirection_t) * original->directions_count);
    
    for (int i = 0; i < original->directions_count; i++) {
        FrontierDirection_t *clone = malloc(sizeof(FrontierDirection_t));
        clone_frontier_direction(clone, original->frontiers[i]);
        // TODO: Strozzi
        dest->frontiers[i] = clone;
    }
}

void clone_frontier_direction(FrontierDirection_t *dest, FrontierDirection_t *original) {
    dest->direction = original->direction;
}

FrontierNode_t *get_pointed_frontier_node(FrontierDirection_t *direction) {

}