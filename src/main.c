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

    // print_full_map(map);

    clock_t start;
    clock_t end;
    float seconds;

    printf("\n === Solving by first segment === \n");
    Map_t *first_segment_clone = malloc(sizeof(Map_t));
    clone_map(first_segment_clone, map);

    start = clock();
    solve_first_segment(first_segment_clone, 1);

    print_solution(first_segment_clone);
    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Total time: %f\n", seconds);

    free_map(first_segment_clone);

    
    printf("\n === Solving by biggest segment === \n");
    Map_t *biggest_segment_clone = malloc(sizeof(Map_t));
    clone_map(biggest_segment_clone, map); 

    start = clock();
    solve_biggest_segment(biggest_segment_clone, 1);
    print_solution(biggest_segment_clone);

    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Total time: %f\n", seconds);

    free_map(biggest_segment_clone);

    
    printf("\n === Solving by biggest resulting segment with 1 === \n");
    Map_t *biggest_resulting_segment_clone = malloc(sizeof(Map_t));
    clone_map(biggest_resulting_segment_clone, map);

    start = clock();
    solve_biggest_resulting_segment(biggest_resulting_segment_clone, 1, 1);
    print_solution(biggest_resulting_segment_clone);

    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Total time: %f\n", seconds);

    free_map(biggest_resulting_segment_clone);

    
    // printf("\n === Solving by biggest resulting segment with 2 === \n");
    // Map_t *biggest_resulting_segment_2_clone = malloc(sizeof(Map_t));
    // clone_map(biggest_resulting_segment_2_clone, map);

    // start = clock();
    // solve_biggest_resulting_segment(biggest_resulting_segment_2_clone, 2, 1);
    // print_solution(biggest_resulting_segment_2_clone);

    // end = clock();
    // seconds = (float)(end - start) / CLOCKS_PER_SEC;
    // printf("Total time: %f\n", seconds);

    // free_map(biggest_resulting_segment_2_clone);

    
    // printf("\n === Solving by biggest resulting segment with 3 === \n");
    // Map_t *biggest_resulting_segment_3_clone = malloc(sizeof(Map_t));
    // clone_map(biggest_resulting_segment_3_clone, map);

    // start = clock();
    // solve_biggest_resulting_segment(biggest_resulting_segment_3_clone, 3, 1);
    // print_solution(biggest_resulting_segment_3_clone);

    // end = clock();
    // seconds = (float)(end - start) / CLOCKS_PER_SEC;
    // printf("Total time: %f\n", seconds);

    // free_map(biggest_resulting_segment_3_clone);

    
    // printf("\n === Solving by biggest resulting segment with 4 === \n");
    // Map_t *biggest_resulting_segment_4_clone = malloc(sizeof(Map_t));
    // clone_map(biggest_resulting_segment_4_clone, map);

    // start = clock();
    // solve_biggest_resulting_segment(biggest_resulting_segment_4_clone, 4, 1);
    // print_solution(biggest_resulting_segment_4_clone);

    // end = clock();
    // seconds = (float)(end - start) / CLOCKS_PER_SEC;
    // printf("Total time: %f\n", seconds);

    // free_map(biggest_resulting_segment_4_clone);

    printf("\n === Solving by most distant segment with 200 === \n");
    Map_t *most_distant_segment_clone_200 = malloc(sizeof(Map_t));
    clone_map(most_distant_segment_clone_200, map);

    start = clock();
    solve_most_distant_segment(most_distant_segment_clone_200, 200, 1);
    print_solution(most_distant_segment_clone_200);

    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Total time: %f\n", seconds);

    free_map(most_distant_segment_clone_200);

    printf("\n === Solving by most distant segment with 100 === \n");
    Map_t *most_distant_segment_clone_100 = malloc(sizeof(Map_t));
    clone_map(most_distant_segment_clone_100, map);

    start = clock();
    solve_most_distant_segment(most_distant_segment_clone_100, 100, 1);
    print_solution(most_distant_segment_clone_100);

    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Total time: %f\n", seconds);

    free_map(most_distant_segment_clone_100);

    printf("\n === Solving by most distant segment with 50 === \n");
    Map_t *most_distant_segment_clone_50 = malloc(sizeof(Map_t));
    clone_map(most_distant_segment_clone_50, map);

    start = clock();
    solve_most_distant_segment(most_distant_segment_clone_50, 50, 1);
    print_solution(most_distant_segment_clone_50);

    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Total time: %f\n", seconds);

    free_map(most_distant_segment_clone_50);

    printf("\n === Solving by most distant segment with 35 === \n");
    Map_t *most_distant_segment_clone_35 = malloc(sizeof(Map_t));
    clone_map(most_distant_segment_clone_35, map);

    start = clock();
    solve_most_distant_segment(most_distant_segment_clone_35, 35, 1);
    print_solution(most_distant_segment_clone_35);

    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Total time: %f\n", seconds);

    free_map(most_distant_segment_clone_35);


    printf("\n === Solving by most distant segment with 20 === \n");
    Map_t *most_distant_segment_clone_20 = malloc(sizeof(Map_t));
    clone_map(most_distant_segment_clone_20, map);

    start = clock();
    solve_most_distant_segment(most_distant_segment_clone_20, 20, 1);
    print_solution(most_distant_segment_clone_20);

    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Total time: %f\n", seconds);

    free_map(most_distant_segment_clone_20);

    printf("\n === Solving by most distant segment with 15 === \n");
    Map_t *most_distant_segment_clone_15 = malloc(sizeof(Map_t));
    clone_map(most_distant_segment_clone_15, map);

    start = clock();
    solve_most_distant_segment(most_distant_segment_clone_15, 15, 1);
    print_solution(most_distant_segment_clone_15);

    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Total time: %f\n", seconds);

    free_map(most_distant_segment_clone_15);


    printf("\n === Solving by most distant segment with 10 === \n");
    Map_t *most_distant_segment_clone_10 = malloc(sizeof(Map_t));
    clone_map(most_distant_segment_clone_10, map);

    start = clock();
    solve_most_distant_segment(most_distant_segment_clone_10, 10, 1);
    print_solution(most_distant_segment_clone_10);

    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Total time: %f\n", seconds);

    free_map(most_distant_segment_clone_10);


    printf("\n === Solving by most distant segment with 4 === \n");
    Map_t *most_distant_segment_clone_4 = malloc(sizeof(Map_t));
    clone_map(most_distant_segment_clone_4, map);

    start = clock();
    solve_most_distant_segment(most_distant_segment_clone_4, 4, 1);
    print_solution(most_distant_segment_clone_4);

    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Total time: %f\n", seconds);

    free_map(most_distant_segment_clone_4);

    
    printf("\n === Solving by most distant segment with 3 === \n");
    Map_t *most_distant_segment_clone_3 = malloc(sizeof(Map_t));
    clone_map(most_distant_segment_clone_3, map);

    start = clock();
    solve_most_distant_segment(most_distant_segment_clone_3, 3, 1);
    print_solution(most_distant_segment_clone_3);

    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Total time: %f\n", seconds);

    free_map(most_distant_segment_clone_3);

    
    printf("\n === Solving by most distant segment with 2 === \n");
    Map_t *most_distant_segment_clone_2 = malloc(sizeof(Map_t));
    clone_map(most_distant_segment_clone_2, map);

    start = clock();
    solve_most_distant_segment(most_distant_segment_clone_2, 2, 1);
    print_solution(most_distant_segment_clone_2);

    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Total time: %f\n", seconds);

    free_map(most_distant_segment_clone_2);

    
    printf("\n === Solving by most distant segment with 1 === \n");
    Map_t *most_distant_segment_clone_1 = malloc(sizeof(Map_t));
    clone_map(most_distant_segment_clone_1, map);

    start = clock();
    solve_most_distant_segment(most_distant_segment_clone_1, 1, 1);
    print_solution(most_distant_segment_clone_1);

    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Total time: %f\n", seconds);

    free_map(most_distant_segment_clone_1);


    printf("\n === Solving by composite === \n");
    Map_t *composite_clone = malloc(sizeof(Map_t));
    clone_map(composite_clone, map);

    start = clock();
    solve(composite_clone);
    print_solution(composite_clone);

    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Total time: %f\n", seconds);

    free_map(composite_clone);

    printf("\n === Solving by best === \n");
    start = clock();
    Map_t *best_map = solve_most_distant_segment_best(map, width * height, 1);
    print_solution(best_map);

    end = clock();
    seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("Total time: %f\n", seconds);

    free_map(best_map);

    free_map(map);
    return 0;
}
