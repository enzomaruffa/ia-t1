#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "segment.h"
#include "map.h"

char has_checked_position(char *checked_xs, char *checked_ys, int size, char x, char y) {
    for (int i = 0; i < size; i++) {
        if (checked_xs[i] == x && checked_ys[i] == y) {
            return 1;
        }
    }
    return 0;
}

void check_neighbour(Segment_t *new_segment,
                        Map_t *map, 
                        char *matrix,
                        char width, 
                        char height, 
                        char x, 
                        char y,
                        FrontierNode_t *parent_node,
                        char delta_x, 
                        char delta_y,
                        Direction direction,
                        char *xs_queue, 
                        char *ys_queue, 
                        int *queue_max_index) {
    char neighbour_x = x + delta_x;
    char neighbour_y = y + delta_y;

    if (neighbour_x > 0 && neighbour_x < width && neighbour_y > 0 && neighbour_y < height) {
        // Check neighbour
        char neighbour_color = matrix[neighbour_y * width + neighbour_x];

        if (neighbour_color == new_segment->color) {
            // Push other to queue
            xs_queue[*queue_max_index] = neighbour_x;
            ys_queue[*queue_max_index] = neighbour_y;
            *queue_max_index += 1;
        } else {                        
            // If neighbour has other color, add a frontier
            FrontierDirection_t *new_frontier = malloc(sizeof(FrontierDirection_t));
            new_frontier->direction = direction;

            // Add to the parent node
            parent_node->frontiers[parent_node->directions_count] = new_frontier;
            parent_node->directions_count += 1;

            // Check if a segment in that position already exists
            FrontierNode_t *pointed_node = NULL;

            for (int i = 0; i < map->segment_count; i++) {
                pointed_node = find_node_by_position(map->segments[i], neighbour_x, neighbour_y);
                if (pointed_node) {
                    break;
                }
            }

            // If exists, make link and backlink
            if (pointed_node) {
                new_frontier->pointed_node = pointed_node;

                Direction opposite = opposite_direction(direction);

                // Find the opposite frontier direction in the node
                for (int i = 0; i < pointed_node->directions_count; i++) {
                    FrontierDirection_t *other_direction = pointed_node->frontiers[i];

                    if (other_direction->direction == opposite) {
                        other_direction->pointed_node = parent_node;
                        break;
                    }
                }
            } 
        }
    }
}

void expand_segment(Segment_t *new_segment, 
                    Map_t *map, 
                    char *matrix, 
                    char *checked_xs, 
                    char *checked_ys, 
                    int *check_size, 
                    char width, 
                    char height, 
                    char *xs_queue, 
                    char *ys_queue, 
                    char original_x, 
                    char original_y) {

    int queue_max_index = 0;
    int queue_check_index = 0;

    xs_queue[queue_max_index] = original_x;
    ys_queue[queue_max_index] = original_y;
    queue_max_index += 1;

    while (queue_check_index < queue_max_index) {
        // Check if has been checked (double added to the queue)
        char queue_x = xs_queue[queue_check_index];
        char queue_y = ys_queue[queue_check_index];
        queue_check_index += 1;

        if (has_checked_position(checked_xs, checked_ys, *check_size, queue_x, queue_y)) {
            continue;
        }

        // Add to checked
        checked_xs[*check_size] = queue_x;
        checked_ys[*check_size] = queue_y;
        *check_size += 1;

        // Add properties to segment
        new_segment->size += 1;

        // Create a node for this position
        FrontierNode_t *node = malloc(sizeof(FrontierNode_t));
        node->directions_count = 0;
        node->frontiers = malloc(sizeof(FrontierDirection_t) * 4);

        // === Check neighbours
        // Check the top neighbour
        check_neighbour(new_segment, map, matrix,
                        width, height, 
                        queue_x, queue_y,
                        node,
                        0, -1, TOP,
                        xs_queue, ys_queue, 
                        &queue_max_index);

        // Check the left neighbour
        check_neighbour(new_segment, map, matrix,
                        width, height, 
                        queue_x, queue_y,
                        node,
                        -1, 0, LEFT,
                        xs_queue, ys_queue, 
                        &queue_max_index);

        // Check the right neighbour
        check_neighbour(new_segment, map, matrix,
                        width, height, 
                        queue_x, queue_y,
                        node,
                        1, 0, RIGHT,
                        xs_queue, ys_queue, 
                        &queue_max_index);

        // Check the bottom neighbour
        check_neighbour(new_segment, map, matrix,
                        width, height, 
                        queue_x, queue_y,
                        node,
                        0, 1, DOWN,
                        xs_queue, ys_queue, 
                        &queue_max_index);

        // Check if node has == 0 directions. If so, delete node
        if (node->directions_count == 0) {
            free_frontier_node(node);
        } else {
            node->parent_segment = new_segment;

            node->frontiers = realloc(node->frontiers, sizeof(FrontierDirection_t) * node->directions_count);

            new_segment->frontiers[new_segment->frontiers_count] = node;
            new_segment->frontiers += 1;
        }
    }
}

void create_map(Map_t *map, char *matrix, char width, char height) {
    map->moves_count = 0;
    map->segment_count = 0;

    int next_segment_id = 0;

    // List of verified nodes
    int check_size = 0;
    char *checked_xs = malloc(sizeof(char) * width * height);
    char *checked_ys = malloc(sizeof(char) * width * height);

    // Stack of nodes to check
    char *xs_queue = malloc(sizeof(char) * width * height);
    char *ys_queue = malloc(sizeof(char) * width * height);

    // TODO: Create segments and moves
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < width; y++) {
            if (!has_checked_position(checked_xs, checked_ys, check_size, x, y)) {
                checked_xs[check_size] = x;
                checked_ys[check_size] = y;
                check_size += 1;

                // Create a new segment
                Segment_t *new_segment = malloc(sizeof(Segment_t));

                new_segment->id = next_segment_id;
                
                next_segment_id += 1;

                new_segment->size = 0;
                new_segment->frontiers_count = 0;
                new_segment->frontiers = malloc(sizeof(FrontierNode_t) * width * height);

                new_segment->color = matrix[y * width + x];

                expand_segment(new_segment, map, matrix, 
                                checked_xs, checked_ys, &check_size,
                                width, height,
                                xs_queue, ys_queue,
                                x, y);

                // Reduce the size of the segments
                new_segment->frontiers = realloc(new_segment->frontiers, sizeof(FrontierNode_t) * new_segment->frontiers_count);

                // Add segment to segments
                map->segments[map->segment_count] = new_segment;
                map->segment_count += 1;
            }
        }
    }

    map->initial_segment = map->segments[0];

    // Reduce the size of the map
    map->segments = realloc(map->segments, sizeof(Segment_t) * map->segment_count);

    free(checked_xs);
    free(checked_ys);
    free(xs_queue);
    free(ys_queue);
}


Segment_t *find_segment_by_id(Map_t *map, char id) {
    for (int i = 0; i < map->segment_count; i++) {
        if (map->segments[i]->id == id) {
            return map->segments[i];
        }
    }
    return NULL;
}

void clone_map(Map_t *dest, Map_t *original) {
    dest->moves_count = original->moves_count;

    int moves_size = sizeof(char) * original->moves_count;
    dest->moves = malloc(moves_size);
    memcpy(dest, original, moves_size);

    dest->segment_count = original->segment_count;

    // Clone segments
    dest->segments = malloc(sizeof(Segment_t) * original->segment_count); 

    for (int i = 0; i < original->segment_count; i++) {
        Segment_t *clone = malloc(sizeof(Segment_t));
        clone_segment(clone, original->segments[i]);
        dest->segments[i] = clone;
    }

    for (int i = 0; i < original->segment_count; i++) {
        if (dest->segments[i]->id == original->initial_segment->id) {
            dest->initial_segment = dest->segments[i];
        }
    }

    // Fix the frontier pointers
    for (int i = 0; i < original->segment_count; i++) {
        Segment_t *original_segment = original->segments[i];
        Segment_t *clone_segment = dest->segments[i];

        for (int j = 0; j < original_segment->frontiers_count; j++) {
            FrontierNode_t *original_frontier = original_segment->frontiers[j];
            FrontierNode_t *clone_frontier = clone_segment->frontiers[j];

            for (int k = 0; k < original_frontier->directions_count; k++) {
                FrontierDirection_t *original_direction = original_frontier->frontiers[k];
                FrontierDirection_t *clone_direction = clone_frontier->frontiers[k];

                // The direction segment ID
                char original_pointed_x = original_direction->pointed_node->x;
                char original_pointed_y = original_direction->pointed_node->y;
                
                FrontierNode_t *clone_pointed_node = find_node_by_position(clone_segment, original_pointed_x, original_pointed_y);

                // Attribute to clone
                clone_direction->pointed_node = clone_pointed_node;
            }
        }
    }

}

void paint_map(Map_t *dest, char color) {

}

void print_map(Map_t *map) {
    
}

void free_map(Map_t *map) {
    for (int i = 0; i < map->segment_count; i++) {
        free_segment(map->segments[i]);
    }
    free(map->segments);
    free(map->moves);
    free(map);
}