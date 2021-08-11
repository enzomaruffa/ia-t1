#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../types/map.h"

Segment_t *forward_propagate(Segment_t *initial_segment, Segment_t **queue_segments) {
    // Set the initial segment properties
    initial_segment->gs_distance_to_initial = 0;
    initial_segment->gs_visited = 1;

    // Breadth search assigning distance and factor
    int current_segment_place = 0;
    int current_segment_iteration = 0;

    queue_segments[current_segment_place] = initial_segment;
    current_segment_place += 1;

    Segment_t *target_segment = initial_segment;

    while (current_segment_iteration < current_segment_place) {
        Segment_t *current_segment = queue_segments[current_segment_iteration];
        current_segment->gs_factor += current_segment->frontiers_count;

        // For each segment I'm touching
        int frontier_segments_count;
        Segment_t **frontier_segments = get_all_frontier_segments(current_segment, &frontier_segments_count);

        for (int k = 0; k < frontier_segments_count; k++) {
            Segment_t *frontier_segment = frontier_segments[k];

            // If not visited, assign distance and set visited
            if (!frontier_segment->gs_visited) {
                frontier_segment->gs_visited = 1;
                frontier_segment->gs_distance_to_initial = current_segment->gs_distance_to_initial + 1;

                // Add to the queue
                queue_segments[current_segment_place] = frontier_segment;
                current_segment_place += 1;
            }

            if (current_segment->gs_distance_to_initial < frontier_segment->gs_distance_to_initial) {
                // Increase the frontier segment gs_factor by my factor
                frontier_segment->gs_factor += current_segment->gs_factor;
            }
        }

        free(frontier_segments);
        current_segment_iteration += 1;

        // Curently prioritizes the one with the biggest distance and smalles factor
        if (current_segment->gs_distance_to_initial > target_segment->gs_distance_to_initial) {
            target_segment = current_segment;
        } else if (current_segment->gs_distance_to_initial == target_segment->gs_distance_to_initial
                    && current_segment->gs_factor < target_segment->gs_factor) {
            target_segment = current_segment;
        }
    }

    return target_segment;
}


void backward_propagate(Segment_t *target_segment, Segment_t **queue_segments) {
    // Set the initial segment properties
    target_segment->gs_distance_to_target = 0;
    target_segment->gs_visited = 1;

    // Breadth search assigning distance and factor
    int current_segment_place = 0;
    int current_segment_iteration = 0;

    queue_segments[current_segment_place] = target_segment;
    current_segment_place += 1;

    while (current_segment_iteration < current_segment_place) {
        Segment_t *current_segment = queue_segments[current_segment_iteration];

        // For each segment I'm touching
        int frontier_segments_count;
        Segment_t **frontier_segments = get_all_frontier_segments(current_segment, &frontier_segments_count);

        for (int k = 0; k < frontier_segments_count; k++) {
            Segment_t *frontier_segment = frontier_segments[k];

            // If not visited, assign distance and set visited
            if (!frontier_segment->gs_visited) {
                frontier_segment->gs_visited = 1;
                frontier_segment->gs_distance_to_target = current_segment->gs_distance_to_target + 1;

                // Add to the queue
                queue_segments[current_segment_place] = frontier_segment;
                current_segment_place += 1;
            }
        }

        free(frontier_segments);
        current_segment_iteration += 1;
    }
}

void update_graph(Map_t *map) {
    // Preprocess - clean segments
    for (int k = 0; k < map->segment_count; k++) {
        Segment_t *segment = map->segments[k];
        segment->gs_distance_to_initial = -1;
        segment->gs_distance_to_target = -1;
        segment->gs_factor = 0;
        segment->gs_visited = 0;
    }
    
    // printf("Allocating queue\n");
    Segment_t **queue_segments = malloc(sizeof(Segment_t *) * map->segment_count);

    // printf("Forward propagating\n");
    Segment_t *target_segment = forward_propagate(map->initial_segment, queue_segments);

    // Reset the visited - can be removed if significant by reversing the use of the visited flag
    for (int k = 0; k < map->segment_count; k++) {
        map->segments[k]->gs_visited = 0;
    }

    // printf("Backward propagating\n");
    backward_propagate(target_segment, queue_segments);

    free(queue_segments);
}

int choose_move(Map_t *map) {
    // printf("[choose_move] New move!\n");
    int frontier_segments_count = 0;
    Segment_t **frontier_segments = get_all_frontier_segments(map->initial_segment, &frontier_segments_count);

    // printf("    [choose_move] Found %d frontier segments\n", frontier_segments_count);

    // // Get the smallest distance we have
    // for (int k = 0; k < frontier_segments_count; k++) {
    //     print_segment(frontier_segments[k]);
    // }

    // Stores the smallest distance for each color
    int *colors_smallest_distances = malloc(sizeof(int) * map->possible_colors);
    memset(colors_smallest_distances, -1, sizeof(int) * map->possible_colors);

    int smallest_distance = frontier_segments[0]->gs_distance_to_target;

    // Get the smallest distance we have
    for (int k = 0; k < frontier_segments_count; k++) {
        Segment_t *seg = frontier_segments[k];

        if (seg->gs_distance_to_target < smallest_distance) {
            smallest_distance = seg->gs_distance_to_target;
        }

        if (colors_smallest_distances[seg->color - 1] > seg->gs_distance_to_target || colors_smallest_distances[seg->color - 1] == -1) {
            colors_smallest_distances[seg->color - 1] = seg->gs_distance_to_target;
        }
    }

    // printf("    [choose_move] Smallest distances: \n");
    // for (int i = 0; i < map->possible_colors; i++) {
    //     printf("%d ", colors_smallest_distances[i]);
    // }
    // printf("\n");

    // printf("    [choose_move] Found smallest distance: %d\n", smallest_distance);

    // NOTE: This one is using the sum of the segments. Another approach is to get the max
    // Get all the sum of the factors for the colors in the smallest_distance_segments
    unsigned long long int *colors_factor_sum = malloc(sizeof(unsigned long long int) * map->possible_colors);
    memset(colors_factor_sum, 0, sizeof(unsigned long long int) * map->possible_colors);

    // NOTE: Assumes that for K possible colors, colors go from [1, K]

    // Get the smallest distance we have
    for (int k = 0; k < frontier_segments_count; k++) {
        Segment_t *seg = frontier_segments[k];
        // printf("    [choose_move] Checking segment %d\n", seg->id);
        // printf("    [choose_move] Segment has color %d\n", seg->color);
        if (colors_smallest_distances[seg->color - 1] == smallest_distance) {
            // printf("    [choose_move] Segment has same distance to smallest! Increasing the color index factor\n");
            colors_factor_sum[(int)seg->color - 1] += seg->gs_factor;
            // printf("    [choose_move] Color index now %d\n", colors_factor_sum[(int)seg->color - 1]);
        }
    }

    // printf("    [choose_move] Color factors: \n");
    // for (int i = 0; i < map->possible_colors; i++) {
    //     printf("%llu ", colors_factor_sum[i]);
    // }
    // printf("\n");

    // Choose the color with the biggest color_factor_sum
    char color = 0;
    unsigned long long int color_factor = 0;

    for (int k = 0; k < map->possible_colors; k++) {
        // printf("        [choose_move] Checking color %d in index %d\n", k + 1, k);
        if (colors_factor_sum[k] > color_factor) {
            // printf("        [choose_move] Bigger than the original color factor: %llu vs %llu\n", colors_factor_sum[k], color_factor);
            color = (char)k;
            color_factor = colors_factor_sum[k];
            // printf("        [choose_move] Color now %d and color factor %llu\n", color, color_factor);
        }
    }

    // NOTE: Assumes that for K possible colors, colors go from [1, K]. So increase 1 in the color.
    // printf("[choose_move] Chose color in index %d\n", color);
    color += 1;
    // printf("[choose_move] Chose color: %d. Smallest distance is %d.\n", color, smallest_distance);

    free(colors_smallest_distances);
    free(colors_factor_sum);
    free(frontier_segments);

    paint_map(map, color);

    // If 0, we reached the target. So, return 1. If 1+ we haven't reached so return 0
    return !smallest_distance;
}

void solve_most_distant_segment(Map_t *map, int moves_before_recalculating, int seg_count_cap) {
    while (map->segment_count > seg_count_cap) {
        // printf("Updating graph\n");
        update_graph(map);

        int moves_done = 0;
        int reached_target = 0;

        while (moves_done < moves_before_recalculating && map->segment_count > 1 && !reached_target) {
            // printf("Choosing move\n");
            reached_target = choose_move(map);
            moves_done += 1;
        }
    }
}