#include <stdlib.h>
#include "frontier.h"
#include "segment.h"

void clone_frontier_direction(FrontierDirection_t *dest, FrontierDirection_t *original) {
    dest->direction = original->direction;
}

void print_frontier_direction(FrontierDirection_t *direction) {

}

void free_frontier_direction(FrontierDirection_t *direction) {
    free(direction);
}

// ===========================

FrontierNode_t *get_pointed_frontier_node(FrontierDirection_t *direction) {
    return direction->pointed_node;
}

void clone_frontier_node(FrontierNode_t *dest, FrontierNode_t *original) {
    dest->x = original->x;
    dest->y = original->y;
    dest->directions_count = original->directions_count;
    
    dest->frontiers = malloc(sizeof(FrontierDirection_t) * original->directions_count);
    
    for (int i = 0; i < original->directions_count; i++) {
        FrontierDirection_t *clone = malloc(sizeof(FrontierDirection_t));
        clone_frontier_direction(clone, original->frontiers[i]);
        clone->parent_node = dest;
        // TODO: Strozzi
        dest->frontiers[i] = clone;
    }
}

void print_frontier_node(FrontierNode_t *node) {

}

void free_frontier_node(FrontierNode_t *node) {
    for (int i = 0; i < node->directions_count; i++) {
        free_frontier_direction(node->frontiers[i]);
    }

    free(node->frontiers);
    free(node);
}
