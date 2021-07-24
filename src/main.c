#include <stdlib.h>
#include <stdio.h>
#include "map.h"
#include "heuristics/biggest_resulting_segment.h"
#include "heuristics/biggest_segment.h"
#include "heuristics/first_segment.h"
#include "heuristics/most_distant_segment.h"
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

    // printf("\n === Solving by first segment === \n");
    // Map_t *first_segment_clone = malloc(sizeof(Map_t));
    // clone_map(first_segment_clone, map);
    // solve_first_segment(first_segment_clone);
    // print_solution(first_segment_clone);
    // free_map(first_segment_clone);

    // printf("\n === Solving by biggest segment === \n");
    // Map_t *biggest_segment_clone = malloc(sizeof(Map_t));
    // clone_map(biggest_segment_clone, map);
    // solve_biggest_segment(biggest_segment_clone);
    // print_solution(biggest_segment_clone);
    // free_map(biggest_segment_clone);

    // printf("\n === Solving by biggest resulting segment with 1 === \n");
    // Map_t *biggest_resulting_segment_clone = malloc(sizeof(Map_t));
    // clone_map(biggest_resulting_segment_clone, map);
    // solve_biggest_resulting_segment(biggest_resulting_segment_clone, 1);
    // print_solution(biggest_resulting_segment_clone);
    // free_map(biggest_resulting_segment_clone);

    // printf("\n === Solving by biggest resulting segment with 2 === \n");
    // Map_t *biggest_resulting_segment_2_clone = malloc(sizeof(Map_t));
    // clone_map(biggest_resulting_segment_2_clone, map);
    // solve_biggest_resulting_segment(biggest_resulting_segment_2_clone, 2);
    // print_solution(biggest_resulting_segment_2_clone);
    // free_map(biggest_resulting_segment_2_clone);

    // printf("\n === Solving by biggest resulting segment with 3 === \n");
    // Map_t *biggest_resulting_segment_3_clone = malloc(sizeof(Map_t));
    // clone_map(biggest_resulting_segment_3_clone, map);
    // solve_biggest_resulting_segment(biggest_resulting_segment_3_clone, 3);
    // print_solution(biggest_resulting_segment_3_clone);
    // free_map(biggest_resulting_segment_3_clone);

    // printf("\n === Solving by biggest resulting segment with 4 === \n");
    // Map_t *biggest_resulting_segment_4_clone = malloc(sizeof(Map_t));
    // clone_map(biggest_resulting_segment_4_clone, map);
    // solve_biggest_resulting_segment(biggest_resulting_segment_4_clone, 4);
    // print_solution(biggest_resulting_segment_4_clone);
    // free_map(biggest_resulting_segment_4_clone);

    printf("\n === Solving by most distant segment === \n");
    Map_t *most_distant_segment_clone = malloc(sizeof(Map_t));
    clone_map(most_distant_segment_clone, map);
    solve_most_distant_segment(most_distant_segment_clone, 4);
    print_solution(most_distant_segment_clone);
    free_map(most_distant_segment_clone);

    free_map(map);
    return 0;
}