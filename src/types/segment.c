#include "segment.h"

void clone_segment(Segment_t *dest, Segment_t *original);
void segment_point_distance(Segment_t *segment, short x, short y);
void merge(Segment_t *segment_1, Segment_t *segment_2);
