#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "frontier.h"
#include "segment.h"
#include "../utils/utils.h"

void clone_segment(Segment_t *dest, Segment_t *original) {
    dest->id = original->id;
    dest->color = original->color;
    dest->size = original->size;
    dest->frontiers_count = original->frontiers_count;

    dest->frontiers = malloc(sizeof(FrontierNode_t) * original->frontiers_count);

    for (int i = 0; i < original->frontiers_count; i++) {
        FrontierNode_t *clone = malloc(sizeof(FrontierNode_t));

        clone_frontier_node(clone, original->frontiers[i]);
        clone->parent_segment = dest;

        dest->frontiers[i] = clone;
    }
}

float segment_point_distance(Segment_t *segment, char i, char j) {
    float smallest_distance = 10000;

    for (int k = 0; k < segment->frontiers_count; k++) {
        FrontierNode_t *node = segment->frontiers[k];
        float squared_distance = point_squared_distance(i, j, node->i, node->j);
        if (squared_distance < smallest_distance) {
            smallest_distance = squared_distance;
        }
    }

    return sqrt(smallest_distance);
}

FrontierNode_t *find_node_by_position(Segment_t *segment, char i, char j) {
    for (int k = 0; k < segment->frontiers_count; k++) {
        FrontierNode_t *node = segment->frontiers[k];

        if (node->i == i && node->j == j) {
            return node;
        }
    }
    return NULL;
}

void merge(Segment_t *segment_1, Segment_t *segment_2) {
    // Create a new segment for copying
    Segment_t *new_segment = malloc(sizeof(Segment_t));

    new_segment->color = segment_1->color;
    new_segment->frontiers_count = segment_1->frontiers_count + segment_2->frontiers_count;

    new_segment->id = segment_1->id;
    new_segment->size = segment_1->size + segment_2->size;

    // Remove frontier_directions from both segments that point to each other
    for (int k = 0; k < segment_1->frontiers_count; k++) {
        FrontierNode_t *node = segment_1->frontiers[k];

        char removed_directions = 0;
        for (int t = 0; t < node->directions_count; t++) {
            FrontierDirection_t *dir = node->frontiers[t];

            if (dir->pointed_node->parent_segment == segment_2) {
                // Free this direction
                // Reduce 1 from the directions count
            }
        }

        // TODO: Fix the directions_count list by repositioning elements to the begininng of the list

        node->directions_count -= removed_directions;

        // TODO: Realloc list
    }

    // TODO: Same code above for segment_2

    // TODO: Remove all frontier nodes that have directions_count = 0
        // Make sure to free those

    // TODO: Allocate a new frontiers list in the new_segment

    // TOOD: Add frontiers from the segment_2 to the segment_clone

    // Copy memory from the new_segment to the segment_1

    // Erase both segments. WATCH OUT on what is being erase // should not use the erase function here
}

void print_segment(Segment_t *segment) {
    printf("Segment %d with size %d, %d frontiers and color %d\n", segment->id, segment->size, segment->frontiers_count, segment->color);
}

void free_segment(Segment_t *segment) {
    for (int i = 0; i < segment->frontiers_count; i++) {
        free_frontier_node(segment->frontiers[i]);
    }

    free(segment->frontiers);
    free(segment);
}