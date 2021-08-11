#ifndef __BIGGESTRESULTINGSEGMENT_H_
#define __BIGGESTRESULTINGSEGMENT_H_

#include "../types/map.h"

// Chooses the color that results in the biggest size of the initial segment in the next lookahead_factor rounds (i.e. simulates lookahead_factor rounds). Currently buggy, if less than lookahead_factor are necessary it returns a response with at least lookahead_factor steps
void solve_biggest_resulting_segment(Map_t *map, int lookahead_factor, int seg_count_cap);

#endif
