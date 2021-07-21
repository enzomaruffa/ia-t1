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

    dest->frontiers = malloc(sizeof(FrontierNode_t *) * original->frontiers_count);

    for (int i = 0; i < original->frontiers_count; i++) {
        FrontierNode_t *clone = malloc(sizeof(FrontierNode_t));

        clone_frontier_node(clone, original->frontiers[i]);
        clone->parent_segment = (struct Segment_t *)dest;

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
    // printf("[find_node_by_position] Starting search for (%d, %d)\n", i, j);
    // print_segment(segment);
    for (int k = 0; k < segment->frontiers_count; k++) {
        FrontierNode_t *node = segment->frontiers[k];
        if (node->i == i && node->j == j) {
            return node;
        }
    }
    // printf("[find_node_by_position] Did not find\n", i, j);
    return NULL;
}


/*
 * Gets a list of all segments touching this segment
 */ 
Segment_t **get_all_frontier_segments(Segment_t *segment, int *found_segments) {
    Segment_t **segments = malloc(sizeof(Segment_t *) * segment->frontiers_count * 4);
    *found_segments = 0;

    for (int k = 0; k < segment->frontiers_count; k++) {
        FrontierNode_t *frontier = segment->frontiers[k];

        for (int t = 0; t < frontier->directions_count; t++) {
            FrontierDirection_t *direction = frontier->frontiers[t];

            Segment_t *pointed_segment = (Segment_t *)direction->pointed_node->parent_segment;

            // Check if we haven't already added this segment
            int has_added_before = 0;

            for (int w = 0; w < *found_segments; w++) {
                if (segments[w] == pointed_segment) {
                    has_added_before = 1;
                    break;
                }
            }

            if (!has_added_before) {
                segments[*found_segments] = pointed_segment;
                *found_segments += 1;
            }
        }
    }

    return segments;
}

char *get_all_frontier_colors(Segment_t *segment, int *found_colors) {
    char *colors = malloc(sizeof(char) * segment->frontiers_count * 4);
    *found_colors = 0;

    // print_segment(segment);

    for (int k = 0; k < segment->frontiers_count; k++) {
        FrontierNode_t *frontier = segment->frontiers[k];

        for (int t = 0; t < frontier->directions_count; t++) {
            FrontierDirection_t *direction = frontier->frontiers[t];

            Segment_t *pointed_segment = (Segment_t *)direction->pointed_node->parent_segment;

            // Check if we haven't already added this segment color
            int has_added_color_before = 0;

            for (int w = 0; w < *found_colors; w++) {
                if (colors[w] == pointed_segment->color) {
                    has_added_color_before = 1;
                    break;
                }
            }

            if (!has_added_color_before) {
                colors[*found_colors] = pointed_segment->color;
                *found_colors += 1;
            }
        }
    }

    // printf("[get_all_frontier_colors] Segment is currently touching %d colors\n", *found_colors);
    return colors;
}


void remove_directions_pointing_segment(Segment_t *segment, Segment_t *pointed_segment) {
    // Remove frontier_directions from both segments that point to each other
    // printf("[remove_directions_pointing_segment] Removing from segment %d pointing to %d\n", segment->id, pointed_segment->id);
    for (int k = 0; k < segment->frontiers_count; k++) {
        FrontierNode_t *node = segment->frontiers[k];
        // print_frontier_node(node);

        // For from max to min
        for (int t = node->directions_count - 1; t >= 0; t--) {
            FrontierDirection_t *dir = node->frontiers[t];

            // printf("[remove_directions_pointing_segment] Checking direction at %d:\n", t);
            // printf("[remove_directions_pointing_segment] Pointed node: %p:\n", dir->pointed_node);
            // printf("[remove_directions_pointing_segment] Pointed node parent segment: %p:\n", dir->pointed_node->parent_segment);
            // printf("[remove_directions_pointing_segment] Pointed node parent segment ID: %d:\n", dir->pointed_node->parent_segment->id);
            // print_frontier_direction(dir);
            if (dir->pointed_node->parent_segment == (struct Segment_t *)pointed_segment) {
                // printf("[remove_directions_pointing_segment] Removing direction!\n");
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

        // print_frontier_node(node);
        if (node->directions_count == 0) {
            // Removes the frontier direction
            // printf("[remove_directionless_frontiers] Removing node!\n");
            remove_frontier_node(segment, k);
        }
    }
}

void merge(Segment_t *segment_1, Segment_t *segment_2) {
    // printf("[merge] Removing directions pointing to each other\n");
    remove_directions_pointing_segment(segment_1, segment_2);
    remove_directions_pointing_segment(segment_2, segment_1);

    // printf("[merge] Removing useless nodes from s1\n");
    remove_directionless_frontiers(segment_1);
    // printf("[merge] Removing useless nodes from s2\n");
    remove_directionless_frontiers(segment_2);

    // printf("[merge] Trying realloc of the segment %d frontiers\n", segment_1->id);
    if (segment_1->frontiers_count + segment_2->frontiers_count > 0) {
        segment_1->frontiers = realloc(segment_1->frontiers, sizeof(FrontierNode_t *) * (segment_1->frontiers_count + segment_2->frontiers_count));

        // Add frontiers from the segment_2 to the segment_1
        for (int k = segment_1->frontiers_count; k < (segment_1->frontiers_count + segment_2->frontiers_count); k++) {
            segment_1->frontiers[k] = segment_2->frontiers[k - segment_1->frontiers_count];
            segment_1->frontiers[k]->parent_segment = (struct Segment_t *)segment_1;
        }

        // Update segment_1 properties
    }

    segment_1->frontiers_count += segment_2->frontiers_count;
    segment_1->size += segment_2->size;

    // printf("[merge] Segment 1 now:\n");
    // print_segment(segment_1);

    // Remove segment_2
    segment_2->frontiers_count = 0;
    if (segment_2->frontiers) {
        // printf("[merge] Freeing the frontiers list for the s2\n");
        free(segment_2->frontiers);
    }
    segment_2->frontiers = NULL;
}

void print_segment(Segment_t *segment) {
    printf("    [print_segment] Segment [%p] id: %d / size: %d / frontiers: %p, frontiers_count: %d / color: %d\n", segment, segment->id, segment->size, segment->frontiers, segment->frontiers_count, segment->color);
}

void remove_frontier_node(Segment_t *segment, int position) {
    FrontierNode_t *node = segment->frontiers[position];
    // printf("[remove_frontier_node] Freeing node!\n");
    free_frontier_node(node);

    // If it's not the last, update positions
    if (segment->frontiers_count - 1 != position) {
        // printf("[remove_frontier_node] Was not the last. Changing positions!!\n");
        segment->frontiers[position] = segment->frontiers[segment->frontiers_count - 1];
    } 

    segment->frontiers_count -= 1;

    if (segment->frontiers_count == 0 && segment->frontiers) {
        // printf("[remove_frontier_node] Freeing frontiers!\n");
        free(segment->frontiers);
        segment->frontiers = NULL;
        // print_segment(segment);
    } else {
        // printf("[remove_frontier_node] Reallocating the list of frontiers on the segment\n");
        segment->frontiers = realloc(segment->frontiers, sizeof(FrontierNode_t *) * segment->frontiers_count);
        // printf("[remove_frontier_node] Now at %p\n", segment->frontiers);
        // print_segment(segment);
    }
}

void free_segment(Segment_t *segment) {
    // printf("[free_segment] Freeing segment at %p: \n", segment);

    // print_segment(segment);
    for (int i = 0; i < segment->frontiers_count; i++) {
        free_frontier_node(segment->frontiers[i]);
    }

    if (segment->frontiers) {
        free(segment->frontiers);
        segment->frontiers = NULL;
    }

    free(segment);
}