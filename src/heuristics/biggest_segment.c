#include <stdlib.h>
#include <stdio.h>
#include "../types/map.h"

void solve_biggest_segment(Map_t *map) {
    while (map->segment_count > 1) {
        printf("[solve_biggest_segment] Solving by the biggest segment. Map has %d segments\n", map->segment_count);

        int found_segments = 0;
        Segment_t **other_segments = get_all_frontier_segments(map->initial_segment, &found_segments);

        Segment_t *segment = NULL;
        int biggest_segment_size = 0;

        for (int k = 0; k < found_segments; k++) {
            if (other_segments[k]->size > biggest_segment_size) {
                segment = other_segments[k];
                biggest_segment_size = segment->size;
            }
        }

        free(other_segments);

        if (segment) {
            print_segment(segment);
            paint_map(map, segment->color);
        }
    }
}