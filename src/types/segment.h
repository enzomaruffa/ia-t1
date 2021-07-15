#ifndef __SEGMENT_H_
#define __SEGMENT_H_
#include "frontier.h"

typedef struct {
    int id;
    int size;
    char color;
    
    int frontiers_count;
    FrontierNode_t **frontiers;
} Segment_t;

/*
 * Clones the segmento. Each FrontierDirection_t respective Segment_t is not cloned, and the pointer is left unassigned
 */ 
void clone_segment(Segment_t *dest, Segment_t *original);

/*
 * Calculates the distance between a segment and a specified coordinate.
 */ 
float segment_point_distance(Segment_t *segment, char i, char j);

/*
 * Find a frontier node with a given X and Y
 */ 
FrontierNode_t *find_node_by_position(Segment_t *segment, char i, char j);

/*
 * Merges two segments in the segment_1
 */
void merge(Segment_t *segment_1, Segment_t *segment_2);

/*
 * Prints a Segment_t;
 */
void print_segment(Segment_t *segment);

/*
 * Removes a FrontierNode_t from a segment at a position
 */
void remove_frontier_node(Segment_t *segment, int position);

/*
 * Frees a Segment_t;
 */
void free_segment(Segment_t *segment);

#endif
