#ifndef __SEGMENT_H_
#define __SEGMENT_H_
#include "frontier.h"

typedef struct {
    short id;
    short size;
    short color;
    
    int frontiers_count;
    FrontierNode_t frontiers[];
} Segment_t;

/*
 * Deep clones the struct
 */ 
void clone_segment(Segment_t *dest, Segment_t *original);

/*
 * Calculates the distance between a segment and a specified coordinate.
 */ 
void segment_point_distance(Segment_t *segment, short x, short y);

/*
 * Merges two segments in the segment_1
 */
void merge(Segment_t *segment_1, Segment_t *segment_2);

#endif
