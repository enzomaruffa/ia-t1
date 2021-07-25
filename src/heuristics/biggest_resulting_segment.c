#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../types/map.h"

// Finds the best possible size in lookahead_factor rounds. Returns the size of the best possible
int best_possible_size(Map_t *map, int lookahead_factor) {
    // printf("[best_possible_size] Called with lookahead of %d. Map has %d segments\n", lookahead_factor, map->segment_count);
    if (lookahead_factor == 0 || map->segment_count == 1) {
        return map->initial_segment->size;
    }

    // if (lookahead_factor == 1) {
    //     // Instead of painting the map, sum the sizes of the neighbours + this node for each possible color
    //     int *sizes = malloc(sizeof(int) * map->possible_colors);
    //     memset(sizes, map->initial_segment->size, sizeof(int) * map->possible_colors);

    //     int segments_count = 0;
    //     Segment_t **frontiers = get_all_frontier_segments(map->initial_segment, &segments_count);

    //     for (int k = 0; k < segments_count; k++) {
    //         Segment_t *seg = frontiers[k];
    //         sizes[seg->color - 1] += seg->size;
    //     }

    //     int biggest_size = 0;

    //     for (int i = 0; i < map->possible_colors; i++) {
    //         if (sizes[i] > biggest_size) {
    //             biggest_size = sizes[i];
    //         }
    //     }

    //     free(frontiers);
    //     free(sizes);

    //     return biggest_size;
    // }

    int found_colors = 0;
    char *possible_colors = get_all_frontier_colors(map->initial_segment, &found_colors);

    int best_size = 0;

    for (int k = 0; k < found_colors; k++) {
        // printf("    [best_possible_size] Checking size for color %d\n", possible_colors[k]);   
        Map_t *color_clone = malloc(sizeof(Map_t));
        clone_map(color_clone, map);
        // printf("    [best_possible_size] Cloned the map!\n");   
        paint_map(color_clone, possible_colors[k]);
        // printf("    [best_possible_size] Painted the map!\n");   

        // TODO: Improve to avoid other solutions that also fill the map with more movements
        int size = map->initial_segment->size;
        if (map->segment_count > 1) {
            // printf("    [best_possible_size] Still needs to solve. Recursive call!\n");   
            size = best_possible_size(color_clone, lookahead_factor - 1);
        }

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
        // printf("[solve_biggest_resulting_segment] Solving by the biggest resulting segment segment. Map has %d segments\n", map->segment_count);

        // If lookahead factor == 1, do the same as currently being done above. 

        // Else:
        int found_colors = 0;
        char *possible_colors = get_all_frontier_colors(map->initial_segment, &found_colors);

        int best_size = 0;
        int best_color = 0;

        for (int k = 0; k < found_colors; k++) {
            // printf("    [solve_biggest_resulting_segment] Checking size for color %d\n", possible_colors[k]);   
            Map_t *color_clone = malloc(sizeof(Map_t));
            clone_map(color_clone, map);
            // printf("    [solve_biggest_resulting_segment] Cloned the map!\n");   
            paint_map(color_clone, possible_colors[k]);
            // printf("    [solve_biggest_resulting_segment] Painted the map!\n");   

            int size = best_possible_size(color_clone, lookahead_factor - 1);
            // printf("    [solve_biggest_resulting_segment] Best size would be %d\n", size);   

            if (size > best_size) {
                // printf("        [solve_biggest_resulting_segment] This size is better than the previous one! Updating...\n");   
                best_size = size;
                best_color = possible_colors[k];
            }

            free_map(color_clone);
        }

        free(possible_colors);

        // printf("[solve_biggest_resulting_segment] Painting with color %d!\n", best_color);
        paint_map(map, best_color);
    }
}