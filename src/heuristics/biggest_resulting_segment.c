#include <stdlib.h>
#include <stdio.h>
#include "../types/map.h"

// Finds the best possible size in lookahead_factor rounds. Returns the size of the best possible
int best_possible_size(Map_t *map, int lookahead_factor) {
    if (lookahead_factor == 0) {
        return map->initial_segment->size;
    }

    int found_colors = 0;
    char *possible_colors = get_all_frontier_colors(map->initial_segment, &found_colors);

    int best_size = 0;

    for (int k = 0; k < found_colors; k++) {
        Map_t *color_clone = malloc(sizeof(Map_t));
        clone_map(color_clone, map);
        paint_map(color_clone, possible_colors[k]);

        int size = best_possible_size(color_clone, lookahead_factor - 1);

        if (size > best_size) {
            best_size = size;
        }

        free_map(color_clone);
    }

    free(possible_colors);

    return best_size;
}

void solve_biggest_resulting_segment(Map_t *map, int lookahead_factor) {
    while (map->segment_count > 1) {
        printf("[solve_biggest_resulting_segment] Solving by the biggest resulting segment segment. Map has %d segments\n", map->segment_count);
            
        int found_colors = 0;
        char *possible_colors = get_all_frontier_colors(map->initial_segment, &found_colors);

        int best_size = 0;
        int best_color = 0;

        for (int k = 0; k < found_colors; k++) {
            printf("    [solve_biggest_resulting_segment] Checking size for color %d\n", possible_colors[k]);   
            Map_t *color_clone = malloc(sizeof(Map_t));
            clone_map(color_clone, map);
            printf("    [solve_biggest_resulting_segment] Cloned the map!\n");   
            paint_map(color_clone, possible_colors[k]);
            printf("    [solve_biggest_resulting_segment] Painted the map!\n");   

            int size = best_possible_size(color_clone, lookahead_factor - 1);
            printf("    [solve_biggest_resulting_segment] Best size would be %d\n", size);   

            if (size > best_size) {
                printf("        [solve_biggest_resulting_segment] This size is better than the previous one! Updating...\n");   
                best_size = size;
                best_color = possible_colors[k];
            }

            free_map(color_clone);
        }

        free(possible_colors);

        printf("[solve_biggest_resulting_segment] Painting with color %d!\n", best_color);
        paint_map(map, best_color);
    }
}