#ifndef __MAP_H_
#define __MAP_H_
#include "segment.h"

typedef struct {
    int moves_count;
    short* moves;

    Segment_t *initial_segment;

    int segment_count;
    Segment_t **segments;
} Map_t;

/*
 * Creates a map based on a matrix
 */
void create_map(Map_t *dest, short **matrix);

/*
 * Finds a segment in a map with a specific ID
 */
Segment_t *find_segment_by_id(Map_t *map, short id);

/*
 * Deep clones the map
 */
void clone_map(Map_t *dest, Map_t *original);

/*
 * Paints the map with a specified color
 */
void paint_map(Map_t *dest, short color);

/*
 * Prints a Map_t;
 */
void print_map(Map_t *map);

#endif