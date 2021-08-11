#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../types/map.h"
#include "most_distant_segment.h"

Map_t *solve_most_distant_segment_best(Map_t *map, int total_map_cells, int seg_count_cap) {
    int check_limit = total_map_cells > 100 ? 100 : total_map_cells;

    // printf("[solve_most_distant_segment_best] Total map cells: %d...\n", total_map_cells);

    Map_t *best_solution = NULL;

    // Any big enough value so that any solution is better
    int best_solution_moves_count = total_map_cells + 10;

    for (int i = 1; i < check_limit; i++) {
        // printf("[solve_most_distant_segment_best] Checking for distance %d...\n", i);
        Map_t *most_distant_segment_clone = malloc(sizeof(Map_t));
        clone_map(most_distant_segment_clone, map);
        solve_most_distant_segment(most_distant_segment_clone, i, seg_count_cap);
        // printf("    [solve_most_distant_segment_best] %d moves!\n", most_distant_segment_clone->moves_count);
        if (most_distant_segment_clone->moves_count <= best_solution_moves_count) {
            if (best_solution) {
                free_map(best_solution);
            }
            best_solution = most_distant_segment_clone;
            best_solution_moves_count = most_distant_segment_clone->moves_count;
        } else {
            free_map(most_distant_segment_clone);
        }
    }

    // printf("Returning the best map %p that solver it in %d moves!\n", best_solution, best_solution_moves_count);

    return best_solution;
}