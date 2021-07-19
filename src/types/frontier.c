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
    if (direction->pointed_node) {
        if (direction->pointed_node->parent_segment) {
            printf("[print_frontier_direction] Direction [%p] %d / pointed node [%p] in (%d, %d) / pointed node segment [%p] id %d\n", direction, direction->direction, direction->pointed_node, direction->pointed_node->i, direction->pointed_node->j, direction->pointed_node->parent_segment, direction->pointed_node->parent_segment->id); 
        } else {
            printf("[print_frontier_direction] Direction [%p] %d / pointed node [%p] in (%d, %d)\n", direction, direction->direction, direction->pointed_node, direction->pointed_node->i, direction->pointed_node->j); 
        }
    } else {
        printf("[print_frontier_direction] Direction [%p] %d / pointed node [%p]\n", direction, direction->direction, direction->pointed_node); 
    }
}

void free_frontier_direction(FrontierDirection_t *direction) {
    // printf("[free_frontier_direction] Freeing direction at %p: \n", direction);
    // print_frontier_direction(direction);
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
    printf("    [print_frontier_node] Node [%p] position: (%d, %d) directions: %d / segment: [%p] / segment ID: %d / segment color: %d\n", node, node->i, node->j, node->directions_count, node->parent_segment, node->parent_segment->id, node->parent_segment->color); 
}


void remove_frontier_direction(FrontierNode_t *node, int position) {
    // printf("[remove_frontier_direction] called with position %d and node: \n", position);
    // print_frontier_node(node);

    FrontierDirection_t *dir = node->frontiers[position];
    free_frontier_direction(dir);

    // If it's not the last, update positions
    if (node->directions_count - 1 != position) {
        node->frontiers[position] = node->frontiers[node->directions_count - 1];
    } 

    node->directions_count -= 1;

    if (node->directions_count == 0) {
        // printf("[remove_frontier_direction] Was the last direction! Freeing the list :)\n");
        free(node->frontiers);
        node->frontiers = NULL;
    } else {
        // printf("[remove_frontier_direction] Reallocating the list to size %d\n",  node->directions_count);
        node->frontiers = realloc(node->frontiers, sizeof(FrontierDirection_t *) * node->directions_count);
        // printf("[remove_frontier_direction] List now is at %p\n",  node->frontiers);
    }
}

void free_frontier_node(FrontierNode_t *node) {
    // printf("[free_frontier_node] Freeing node at %p: \n", node);
    // print_frontier_node(node);

    for (int i = 0; i < node->directions_count; i++) {
        // printf("[free_frontier_node] Freeing direction %d\n", i);
        free_frontier_direction(node->frontiers[i]);
    }

    if (node->frontiers) {
        // printf("[free_frontier_node] Still had a frontiers list, so freeing it...\n");
        free(node->frontiers);
        node->frontiers = NULL;
    }

    free(node);
}
