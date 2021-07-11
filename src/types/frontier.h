#ifndef __FRONTIER_H_
#define __FRONTIER_H_
// TODO: Strozzi
struct Segment_t {
    char id;
};

struct FrontierNode_t { 
    char i;
    char j;
};

typedef enum {
    TOP,
    RIGHT,
    DOWN,
    LEFT,
} Direction;

Direction opposite_direction(Direction direction);

typedef struct FrontierDirection_t {
    Direction direction;
    struct FrontierNode_t *pointed_node;
    struct FrontierNode_t *parent_node;
} FrontierDirection_t;

/*
 * Clones the frontier_direction. The parent_node and pointed_direction is not cloned, and the pointer is left unassigned
 */
void clone_frontier_direction(FrontierDirection_t *dest, FrontierDirection_t *original);

/*
 * Prints a FrontierDirection_t
 */
void print_frontier_direction(FrontierDirection_t *direction);

/*
 * Frees a FrontierDirection_t
 */
void free_frontier_direction(FrontierDirection_t *direction);

typedef struct {
    char i;
    char j;

    int directions_count;
    FrontierDirection_t **frontiers;

    struct Segment_t *parent_segment;
} FrontierNode_t;

/*
 * Gets the Frontier Node that a direction is pointing
 */
FrontierNode_t *get_pointed_frontier_node(FrontierDirection_t *direction);

/*
 * Clones the frontier node. Each direction pointers is not cloned, and the pointer is left unassigned. The parent_segment is also left unassigned
 */
void clone_frontier_node(FrontierNode_t *dest, FrontierNode_t *original);

/*
 * Prints a FrontierNode_t
 */
void print_frontier_node(FrontierNode_t *node);

/*
 * Frees a FrontierNode_t
 */
void free_frontier_node(FrontierNode_t *node);

#endif
