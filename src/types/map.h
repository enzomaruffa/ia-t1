#ifndef __MAP_H_
#define __MAP_H_
#include "segment.h"

typedef struct {
    int moves_count;
    short* moves;

    Segment_t *initial_segment;

    int segment_count;
    Segment_t *segments[];
} Map_t;


/*
 * Creates a map based on a matrix
 */
void create_map(Map_t *dest, short **matrix);

/*
 * Deep clones the map
 */
void clone_map(Map_t *dest, Map_t *original);

/*
 * Paints the map with a specified color
 */
void paint_map(Map_t *dest, short color);

#endif