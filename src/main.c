#include <stdlib.h>
#include <stdio.h>
#include "map.h"
#include "heuristics/first_segment.h"
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
    create_map(map, map_cells, width, height);

    free(map_cells);

    print_full_map(map);

    Map_t *map_clone = malloc(sizeof(Map_t));

    clone_map(map_clone, map);

    print_full_map(map_clone);

    // solve_first_segment(map);

    // printf("\n === Found a solution! Printing it === \n");

    // print_solution(map);

    free_map(map);
    return 0;
}