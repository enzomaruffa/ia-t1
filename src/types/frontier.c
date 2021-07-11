#include <stdlib.h>
#include <stdio.h>
#include "frontier.h"
#include "segment.h"

inline Direction opposite_direction(Direction direction) {
    return (direction + 2) % 4;
}

// ===========================

void clone_frontier_direction(FrontierDirection_t *dest, FrontierDirection_t *original) {
    dest->direction = original->direction;
}

void print_frontier_direction(FrontierDirection_t *direction) {
    printf("Direction %d pointing to node in (%d, %d)\n", direction->direction, direction->pointed_node->i, direction->pointed_node->j); 
}

void free_frontier_direction(FrontierDirection_t *direction) {
    free(direction);
}

// ===========================

FrontierNode_t *get_pointed_frontier_node(FrontierDirection_t *direction) {
    return direction->pointed_node;
}

void clone_frontier_node(FrontierNode_t *dest, FrontierNode_t *original) {
    dest->i = original->i;
    dest->j = original->j;
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
    printf("Node in (%d, %d), with %d directions that belongs to segment with ID %d\n", node->i, node->j, node->directions_count, node->parent_segment->id); 
}

void free_frontier_node(FrontierNode_t *node) {
    for (int i = 0; i < node->directions_count; i++) {
        free_frontier_direction(node->frontiers[i]);
    }

    free(node->frontiers);
    free(node);
}
