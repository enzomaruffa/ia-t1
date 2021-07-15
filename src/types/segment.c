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

void remove_directions_pointing_segment(Segment_t *segment, Segment_t *pointed_segment) {
    // Remove frontier_directions from both segments that point to each other
    for (int k = 0; k < segment->frontiers_count; k++) {
        FrontierNode_t *node = segment->frontiers[k];

        // For from max to min
        for (int t = node->directions_count - 1; t >= 0; t--) {
            FrontierDirection_t *dir = node->frontiers[t];

            if (dir->pointed_node->parent_segment == pointed_segment) {
                // Removes the frontier direction
                remove_frontier_direction(node, t);
            }
        }

        node->frontiers = realloc(node->frontiers, sizeof(FrontierDirection_t) * node->directions_count);
    }
}

void remove_directionless_frontiers(Segment_t *segment) {
    // For from max to min
    for (int k = segment->frontiers_count - 1; k >= 0; k--) {
        FrontierNode_t *node = segment->frontiers[k];

        if (node->directions_count == 0) {
            // Removes the frontier direction
            remove_frontier_node(segment, k);
        }
    }

    segment->frontiers = realloc(segment->frontiers, sizeof(FrontierNode_t) * segment->frontiers_count);
}

void merge(Segment_t *segment_1, Segment_t *segment_2) {
    remove_directions_pointing_segment(segment_1, segment_2);
    remove_directions_pointing_segment(segment_2, segment_1);

    remove_directionless_frontiers(segment_1);
    remove_directionless_frontiers(segment_2);

    // Reallocate the frontiers list in the segment_1
    segment_1->frontiers = realloc(segment_1->frontiers, sizeof(FrontierNode_t) * segment_1->frontiers_count + segment_2->frontiers_count);

    // Add frontiers from the segment_2 to the segment_1
    for (int k = segment_1->frontiers_count; k < segment_1->frontiers_count + segment_2->frontiers_count; k++) {
        segment_1->frontiers[k] = segment_2->frontiers[k - segment_1->frontiers_count];
    }

    // Update segment_1 properties
    segment_1->frontiers_count += segment_2->frontiers_count;
    segment_1->size += segment_2->size;

    // TODO: Delete segment 2
}

void print_segment(Segment_t *segment) {
    printf("Segment %d with size %d, %d frontiers and color %d\n", segment->id, segment->size, segment->frontiers_count, segment->color);
}

void remove_frontier_node(Segment_t *segment, int position) {
    FrontierNode_t *node = segment->frontiers[position];
    free_frontier_node(node);

    // If it's not the last, update positions
    if (segment->frontiers_count - 1 != position) {
        segment->frontiers[position] = segment->frontiers[segment->frontiers_count - 1];
    } 

    segment->frontiers_count -= 1;

    if (segment->frontiers_count == 0) {
        free(segment->frontiers);
    } else {
        segment->frontiers = realloc(segment->frontiers, sizeof(FrontierNode_t) * segment->frontiers_count);
    }
}

void free_segment(Segment_t *segment) {
    for (int i = 0; i < segment->frontiers_count; i++) {
        free_frontier_node(segment->frontiers[i]);
    }

    free(segment->frontiers);
    free(segment);
}