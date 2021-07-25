#ifndef __MOSTDISTANTSEGMENT_H_
#define __MOSTDISTANTSEGMENT_H_

#include "../types/map.h"

// Chooses the shortest path to the most distant segment
// If multiple colors have the shortest path, chooses the one with the highest factor
void solve_most_distant_segment(Map_t *map, int moves_before_recalculating, int seg_count_cap);

#endif
