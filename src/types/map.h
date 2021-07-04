#ifndef __MAP_H_
#define __MAP_H_
#include "segment.h"

struct Map_t {
    int moves_count;
    short* moves;

    Segment_t *initial_segment;

    int segment_count;
    Segment_t *segments[];
};

void create_map(Map_t *dest, short **matrix);
void clone_map(Map_t *dest, Map_t *original);
void paint_map(Map_t *dest, short color);

#endif