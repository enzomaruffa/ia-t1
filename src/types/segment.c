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
    // printf("= Removing from segment %d pointing to %d\n", segment->id, pointed_segment->id);
    for (int k = 0; k < segment->frontiers_count; k++) {
        FrontierNode_t *node = segment->frontiers[k];
        // printf("== Checking node at %d in (%d, %d), pointer %p:\n", k, node->i, node->j, node);

        // For from max to min
        for (int t = node->directions_count - 1; t >= 0; t--) {
            FrontierDirection_t *dir = node->frontiers[t];

            // printf("==== Checking direction at %d:\n", t);
            // print_frontier_direction(dir);
            if (dir->pointed_node->parent_segment == pointed_segment) {
                // printf("====== Removing it!\n");
                // Removes the frontier direction
                remove_frontier_direction(node, t); 
            }
        }
    }
}

void remove_directionless_frontiers(Segment_t *segment) {
    // For from max to min
    for (int k = segment->frontiers_count - 1; k >= 0; k--) {
        FrontierNode_t *node = segment->frontiers[k];

        // printf("==== Checking node at %d in (%d, %d) with pointer %p:\n", k, node->i, node->j, node);
        if (node->directions_count == 0) {
            // Removes the frontier direction
            // printf("====== Removing it!\n");
            remove_frontier_node(segment, k);
        }
    }
}

void merge(Segment_t *segment_1, Segment_t *segment_2) {
    // printf("== Removing directions pointing to each other\n");
    remove_directions_pointing_segment(segment_1, segment_2);
    remove_directions_pointing_segment(segment_2, segment_1);

    // TODO: Remove later
    for (int i = 0; i < segment_2->frontiers_count; i++) {
        // printf("== Checking node at %d in (%d, %d), pointer %p:\n", i, segment_2->frontiers[i]->i, segment_2->frontiers[i]->j, segment_2->frontiers[i]);
    }

    // printf("== Removing nodes\n");
    // printf("== Removing from s1\n");
    remove_directionless_frontiers(segment_1);
    // printf("== Removing from s2\n");
    remove_directionless_frontiers(segment_2);

    // TODO: Remove later
    for (int i = 0; i < segment_2->frontiers_count; i++) {
        // printf("== Checking node at %d in (%d, %d), pointer %p:\n", i, segment_2->frontiers[i]->i, segment_2->frontiers[i]->j, segment_2->frontiers[i]);
    }

    // Reallocate the frontiers list in the segment_1
    // printf("== Reallocating frontiers:\n");
    // printf("===== Segment 1 has %d frontiers:\n", segment_1->frontiers_count);
    // printf("===== Segment 2 has %d frontiers:\n", segment_2->frontiers_count);
    segment_1->frontiers = realloc(segment_1->frontiers, sizeof(FrontierNode_t *) * (segment_1->frontiers_count + segment_2->frontiers_count));

    // Add frontiers from the segment_2 to the segment_1
    // printf("===== K going from %d to %d:\n", segment_1->frontiers_count, segment_1->frontiers_count + segment_2->frontiers_count);
    for (int k = segment_1->frontiers_count; k < (segment_1->frontiers_count + segment_2->frontiers_count); k++) {
        // printf("===== K is %d\n", k);
        // printf("===== Adding segment 2 frontier index %d to segment 1 frontier index %d\n", k - segment_1->frontiers_count, k);
        segment_1->frontiers[k] = segment_2->frontiers[k - segment_1->frontiers_count];
        segment_1->frontiers[k]->parent_segment = segment_1;
    }

    // Update segment_1 properties
    segment_1->frontiers_count += segment_2->frontiers_count;
    segment_1->size += segment_2->size;

    // printf("=== Segment 1 now has %d frontiers\n", segment_1->frontiers_count);

    // TODO: Remove later
    for (int i = 0; i < segment_1->frontiers_count; i++) {
        // printf("== Node at %d in (%d, %d), pointer %p:\n", i, segment_1->frontiers[i]->i, segment_1->frontiers[i]->j, segment_1->frontiers[i]);
    }

    segment_2->frontiers_count = 0;
    if (segment_2->frontiers) {
        free(segment_2->frontiers);
    }
    segment_2->frontiers = NULL;
}

void print_segment(Segment_t *segment) {
    printf("Segment %d with size %d, %d frontiers and color %d\n", segment->id, segment->size, segment->frontiers_count, segment->color);
}

void remove_frontier_node(Segment_t *segment, int position) {
    FrontierNode_t *node = segment->frontiers[position];
    // printf("========= Freeing node!\n");
    free_frontier_node(node);

    // If it's not the last, update positions
    if (segment->frontiers_count - 1 != position) {
        // printf("========= Changing pos!\n");
        segment->frontiers[position] = segment->frontiers[segment->frontiers_count - 1];
    } 

    segment->frontiers_count -= 1;

    if (segment->frontiers_count == 0) {
        // printf("========= Freeing frontier!\n");
        free(segment->frontiers);
        segment->frontiers = NULL;
    } else {
        segment->frontiers = realloc(segment->frontiers, sizeof(FrontierNode_t *) * segment->frontiers_count);
    }
}

void free_segment(Segment_t *segment) {
    for (int i = 0; i < segment->frontiers_count; i++) {
        free_frontier_node(segment->frontiers[i]);
    }

    if (segment->frontiers) {
        free(segment->frontiers);
        segment->frontiers = NULL;
    }

    free(segment);
}