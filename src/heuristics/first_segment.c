#include <stdlib.h>
#include <stdio.h>
#include "../types/map.h"

void solve_first_segment(Map_t *map) {
    while (map->segment_count > 1) {
        Segment_t *segment = NULL;

        printf("\n[solve_first_segment] Solving by the first segment. Map has %d segments\n", map->segment_count);

        // Find the first segment that is not the initial segment
        FrontierDirection_t *direction = map->initial_segment->frontiers[0]->frontiers[0];
        segment = (Segment_t *)(direction->pointed_node->parent_segment);

        if (segment) {
            print_segment(segment);
            // Get the color of the first segment
            // Paint with that color
            paint_map(map, segment->color);
            // printf("[solve_first_segment] Finished map paint! \n");
        }
    }
}