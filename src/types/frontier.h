#ifndef __FRONTIER_H_
#define __FRONTIER_H_
#include "segment.h"

enum Direction {
    TOP,
    LEFT,
    RIGHT,
    DOWN,
};

struct FrontierDirection_t {
    Direction direction;
    Segment_t *segment;
};
void clone_frontier_direction(FrontierDirection_t *dest, FrontierDirection_t *original);
FrontierNode_t *get_pointed_frontier_node(FrontierDirection_t *direction);

struct FrontierNode_t {
    short x;
    short y;

    int directions_count;
    FrontierDirection_t frontiers[];
};
void clone_frontier_node(FrontierNode_t *dest, FrontierNode_t *original);

#endif
