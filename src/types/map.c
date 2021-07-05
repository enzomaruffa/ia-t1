#include <stdlib.h>
#include <string.h>
#include "segment.h"
#include "map.h"

void create_map(Map_t *dest, short **matrix) {

}

void clone_map(Map_t *dest, Map_t *original) {
    dest->moves_count = original->moves_count;

    int moves_size = sizeof(short) * original->moves_count;
    dest->moves = malloc(moves_size);
    memcpy(dest, original, moves_size);

    dest->segment_count = original->segment_count;

    // Clone segments
    dest->segments = malloc(sizeof(Segment_t) * original->segment_count); 

    for (int i = 0; i < original->segment_count; i++) {
        Segment_t *clone = malloc(sizeof(Segment_t));
        clone_segment(clone, original->segments[i]);
        dest->segments[i] = clone;
    }

    for (int i = 0; i < original->segment_count; i++) {
        if (dest->segments[i]->id == original->initial_segment->id) {
            dest->initial_segment = dest->segments[i];
        }
    }

    // Fix the frontier pointers
    for (int i = 0; i < original->segment_count; i++) {
        Segment_t *original_segment = original->segments[i];
        Segment_t *clone_segment = dest->segments[i];

        for (int j = 0; j < original_segment->frontiers_count; j++) {
            FrontierNode_t *original_frontier = original_segment->frontiers[j];
            FrontierNode_t *clone_frontier = clone_segment->frontiers[j];

            for (int k = 0; k < original_frontier->directions_count; k++) {
                FrontierDirection_t *original_direction = original_frontier->frontiers[k];
                FrontierDirection_t *clone_direction = clone_frontier->frontiers[k];

                // The direction segment ID
                short segment_id = original_direction->segment->id;

                Segment_t *clone_direction_result = find_segment_by_id(dest, segment_id);

                // Attribute to clone
                clone_direction->segment = clone_direction_result;
            }
        }
    }

}

void paint_map(Map_t *dest, short color) {

}

Segment_t *find_segment_by_id(Map_t *map, short id) {
    for (int i = 0; i < map->segment_count; i++) {
        if (map->segments[i]->id == id) {
            return map->segments[i];
        }
    }
    return NULL;
}