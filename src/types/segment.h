#ifndef __SEGMENT_H_
#define __SEGMENT_H_
#include "frontier.h"

struct Segment_t {
    short size;
    short color;
    
    int frontiers_count;
    FrontierNode_t frontiers[];
};

void clone_segment(Segment_t *dest, Segment_t *original);
void segment_point_distance(Segment_t *segment, short x, short y);
void merge(Segment_t *segment_1, Segment_t *segment_2);

#endif
