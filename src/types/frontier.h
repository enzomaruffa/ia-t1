#ifndef __FRONTIER_H_
#define __FRONTIER_H_
// TODO: Strozzi
struct Segment_t { char id; };

typedef enum {
    TOP,
    LEFT,
    RIGHT,
    DOWN,
} Direction;

typedef struct {
    Direction direction;
    struct Segment_t *segment;
} FrontierDirection_t;

/*
 * Clones the frontier_direction. The Segment_t is not cloned, and the pointer is left unassigned
 */
void clone_frontier_direction(FrontierDirection_t *dest, FrontierDirection_t *original);

/*
 * Prints a FrontierDirection_t
 */
void print_frontier_direction(FrontierDirection_t *direction);

typedef struct {
    char x;
    char y;

    int directions_count;
    FrontierDirection_t **frontiers;
} FrontierNode_t;

/*
 * Gets the Frontier Node that a direction is pointing
 */
FrontierNode_t *get_pointed_frontier_node(FrontierDirection_t *direction);

/*
 * Clones the frontier node. Each direction Segment_t is not cloned, and the pointer is left unassigned
 */
void clone_frontier_node(FrontierNode_t *dest, FrontierNode_t *original);

/*
 * Prints a FrontierNode_t
 */
void print_frontier_node(FrontierNode_t *node);

#endif
