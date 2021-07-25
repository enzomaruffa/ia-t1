#ifndef __MAP_H_
#define __MAP_H_
#include "segment.h"

typedef struct {
    char possible_colors;

    int moves_count;
    char* moves;

    Segment_t *initial_segment;

    int segment_count;
    Segment_t **segments;
} Map_t;

/*
 * Creates a map based on a matrix
 */
void create_map(Map_t *map, char *matrix, char width, char height, char possible_colors);

/*
 * Finds a segment in a map with a specific ID
 */
Segment_t *find_segment_by_id(Map_t *map, int id);

/*
 * Finds the largest non-initial segment
 */
Segment_t *find_largest_non_initial_segment(Map_t *map);

/*
 * Deep clones the map
 */
void clone_map(Map_t *dest, Map_t *original);

/*
 * Paints the map with a specified color
 */
void paint_map(Map_t *dest, char color);

/*
 * Prints a Map_t;
 */
void print_map(Map_t *map);

/*
 * Prints a full description of Map_t;
 */
void print_full_map(Map_t *map);

/*
 * Prints the solution for a given map (move count + moves)
 */
void print_solution(Map_t *map);

/*
 * Removes a Segment_t from a segment with an ID
 */
void remove_segment_with_id(Map_t *map, int id);

/*
 * Removes a Segment_t from a segment at a position
 */
void remove_segment(Map_t *map, int position);

/*
 * Frees a Map_t
 */
void free_map(Map_t *map);


#endif