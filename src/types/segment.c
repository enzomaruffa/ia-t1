#include <stdlib.h>
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
        dest->frontiers[i] = clone;
    }
}

float segment_point_distance(Segment_t *segment, char x, char y) {
    float smallest_distance = 10000;

    for (int i = 0; i < segment->frontiers_count; i++) {
        FrontierNode_t *node = segment->frontiers[i];
        float squared_distance = point_squared_distance(x, y, node->x, node->y);
        if (squared_distance < smallest_distance) {
            smallest_distance = squared_distance;
        }
    }

    return sqrt(smallest_distance);
}

void merge(Segment_t *segment_1, Segment_t *segment_2) {

}
