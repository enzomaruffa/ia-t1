#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "map.h"
#include "heuristics/biggest_resulting_segment.h"
#include "heuristics/biggest_segment.h"
#include "heuristics/first_segment.h"
#include "heuristics/most_distant_segment.h"
#include "heuristics/composite_heuristic.h"
#include "heuristics/most_distant_segment_best.h"
#include "utils/utils.h"

int main() {
    char width;
    char height;
    char colors_count;

    read_parameters(&width, &height, &colors_count);

    int total_cells = width * height;

    char *map_cells = malloc(sizeof(char) * total_cells);
    read_map(map_cells, height);

    Map_t *map = malloc(sizeof(Map_t));
    create_map(map, map_cells, width, height, colors_count);

    free(map_cells);

    // clock_t start;
    // clock_t end;
    // float seconds;

    // Actually solve it
    // start = clock();
    Map_t *best_map = solve_most_distant_segment_best(map, width * height, 1);
    print_solution(best_map);

    // end = clock();
    // seconds = (float)(end - start) / CLOCKS_PER_SEC;
    // printf("Total time: %f\n", seconds);

    free_map(best_map);

    free_map(map);
    return 0;
}
