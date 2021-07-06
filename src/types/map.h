#ifndef __MAP_H_
#define __MAP_H_
#include "segment.h"

typedef struct {
    int moves_count;
    char* moves;

    Segment_t *initial_segment;

    int segment_count;
    Segment_t **segments;
} Map_t;

/*
 * Creates a map based on a matrix
 */
void create_map(Map_t *map, char *matrix, char width, char height);

/*
 * Finds a segment in a map with a specific ID
 */
Segment_t *find_segment_by_id(Map_t *map, char id);

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
 * Frees a Map_t
 */
void free_map(Map_t *map);


#endif