#include <stdlib.h>
#include <stdio.h>
#include "map.h"
#include "heuristics/biggest_segment.h"
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

    printf("\n === Solving by first segment === \n");
    Map_t *first_segment_clone = malloc(sizeof(Map_t));
    clone_map(first_segment_clone, map);
    solve_first_segment(first_segment_clone);
    print_solution(first_segment_clone);
    free_map(first_segment_clone);

    printf("\n === Solving by biggest segment === \n");
    Map_t *biggest_segment_clone = malloc(sizeof(Map_t));
    clone_map(biggest_segment_clone, map);
    solve_biggest_segment(biggest_segment_clone);
    print_solution(biggest_segment_clone);
    free_map(biggest_segment_clone);

    free_map(map);
    return 0;
}