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
    printf("Direction %d pointing to node in (%d, %d) which belongs to segment %d and has color %d\n", direction->direction, direction->pointed_node->i, direction->pointed_node->j, direction->pointed_node->parent_segment->id, direction->pointed_node->parent_segment->color); 
}

void free_frontier_direction(FrontierDirection_t *direction) {
    free(direction);
}

// ===========================

FrontierNode_t *get_pointed_frontier_node(FrontierDirection_t *direction) {
    return (FrontierNode_t *)direction->pointed_node;
}

void clone_frontier_node(FrontierNode_t *dest, FrontierNode_t *original) {
    dest->i = original->i;
    dest->j = original->j;
    dest->directions_count = original->directions_count;
    
    dest->frontiers = malloc(sizeof(FrontierDirection_t *) * original->directions_count);
    
    for (int i = 0; i < original->directions_count; i++) {
        FrontierDirection_t *clone = malloc(sizeof(FrontierDirection_t));
        clone_frontier_direction(clone, original->frontiers[i]);
        clone->parent_node = (struct FrontierNode_t *)dest;
        // TODO: Strozzi
        dest->frontiers[i] = clone;
    }
}

void print_frontier_node(FrontierNode_t *node) {
    // print_segment(node->parent_segment);
    printf("Node in (%d, %d), with %d directions that belongs to segment with ID %d and color %d\n", node->i, node->j, node->directions_count, node->parent_segment->id, node->parent_segment->color); 
}


void remove_frontier_direction(FrontierNode_t *node, int position) {
    FrontierDirection_t *dir = node->frontiers[position];
    free_frontier_direction(dir);

    // If it's not the last, update positions
    if (node->directions_count - 1 != position) {
        node->frontiers[position] = node->frontiers[node->directions_count - 1];
    } 

    node->directions_count -= 1;

    if (node->directions_count == 0) {
        free(node->frontiers);
        node->frontiers = NULL;
    } else {
        node->frontiers = realloc(node->frontiers, sizeof(FrontierDirection_t *) * node->directions_count);
    }
}

void free_frontier_node(FrontierNode_t *node) {
    for (int i = 0; i < node->directions_count; i++) {
        free_frontier_direction(node->frontiers[i]);
    }

    if (node->frontiers) {
        free(node->frontiers);
        node->frontiers = NULL;
    }

    free(node);
}
