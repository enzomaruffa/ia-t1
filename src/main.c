#include <stdlib.h>
#include <stdio.h>
#include "map.h"
#include "utils/utils.h"

int main() {
    char width;
    char height;
    char colors_count;

    read_parameters(&width, &height, &colors_count);

    int total_cells = width * height;

    // Allocate necessary space - should not fail
    char *map_cells = malloc(sizeof(char) * total_cells);
    read_map(map_cells, height);

    Map_t *map = malloc(sizeof(Map_t));
    create_map(map, map_cells, width, height);

    // print_full_map(map);

    paint_map(map, 2);
    paint_map(map, 1);
    print_solution(map);

    // print_full_map(map);

    free_map(map);
    return 0;
}