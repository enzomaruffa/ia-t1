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
                        char i, 
                        char j,
                        FrontierNode_t *parent_node,
                        char delta_i, 
                        char delta_j,
                        Direction direction,
                        char *is_queue, 
                        char *js_queue, 
                        int *queue_max_index) {
    char neighbour_i = i + delta_i;
    char neighbour_j = j + delta_j;

    // printf("            Checking neighbour in %d, %d against %d, %d\n", neighbour_i, neighbour_j, width, height);

    if (neighbour_i >= 0 && neighbour_i < height && neighbour_j >= 0 && neighbour_j < width) {
        // Check neighbour
        char neighbour_color = matrix[neighbour_i * width + neighbour_j];
        // printf("                Neighbour has color %d\n", neighbour_color);

        if (neighbour_color == new_segment->color) {
            // Push other to queue
            // printf("                Neighbour belongs to the same color! Pushing to the queue...\n");
            is_queue[*queue_max_index] = neighbour_i;
            js_queue[*queue_max_index] = neighbour_j;
            *queue_max_index += 1;
        } else {                        
            // If neighbour has other color, add a frontier
            // printf("                Neighbour is from a diff segment\n");
            FrontierDirection_t *new_frontier = malloc(sizeof(FrontierDirection_t));
            new_frontier->direction = direction;
            new_frontier->pointed_node = NULL;

            // Add to the parent node
            // printf("                Adding to the parent node\n");
            parent_node->frontiers[parent_node->directions_count] = new_frontier;
            parent_node->directions_count += 1;

            // Check if a segment in that position already exists
            FrontierNode_t *pointed_node = NULL;

            // printf("                Searching for the pointed_node\n");
            for (int k = 0; k < map->segment_count; k++) {
                // printf("                Checking segment in k: %d\n", k);
                // print_map(map);
                pointed_node = find_node_by_position(map->segments[k], neighbour_i, neighbour_j);
                if (pointed_node) {
                    // printf("                Found the pointed nod1e\n");
                    break;
                }
            }

            // If exists, make link and backlink
            if (pointed_node) {
                // printf("                Pointed node:\n");
                // print_frontier_node(pointed_node);
                new_frontier->pointed_node = (struct FrontierNode_t *)pointed_node;

                Direction opposite = opposite_direction(direction);

                // printf("                Looking for the frontier with direction %d, which is opposite to our %d in the other node!\n", opposite, direction);
                // Find the opposite frontier direction in the node
                for (int k = 0; k < pointed_node->directions_count; k++) {
                    FrontierDirection_t *other_direction = pointed_node->frontiers[k];
                    // printf("                For k %d, other_direction is %d\n", k, other_direction->direction);

                    if (other_direction->direction == opposite) {
                        // printf("                Found frontier in the other. Backlink created!\n");
                        other_direction->pointed_node = (struct FrontierNode_t *)parent_node;
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
                    char *checked_is, 
                    char *checked_js, 
                    int *check_size, 
                    char width, 
                    char height, 
                    char *is_queue, 
                    char *js_queue, 
                    char original_i, 
                    char original_j) {

    int queue_max_index = 0;
    int queue_check_index = 0;

    is_queue[queue_max_index] = original_i;
    js_queue[queue_max_index] = original_j;
    queue_max_index += 1;

    // printf("    Added %d, %d to the queue\n", original_i, original_j);

    while (queue_check_index < queue_max_index) {
        // Check if has been checked (double added to the queue)
        char queue_i = is_queue[queue_check_index];
        char queue_j = js_queue[queue_check_index];
        queue_check_index += 1;

        // printf("    Checking %d, %d from the queue\n", queue_i, queue_j);

        if (has_checked_position(checked_is, checked_js, *check_size, queue_i, queue_j)) {
            // printf("        Had previously checked... Returning\n");
            continue;
        }

        // Add to checked
        checked_is[*check_size] = queue_i;
        checked_js[*check_size] = queue_j;
        *check_size += 1;

        // Add properties to segment
        new_segment->size += 1;

        // Create a node for this position
        FrontierNode_t *node = malloc(sizeof(FrontierNode_t));
        node->parent_segment = (struct Segment_t *)new_segment;
        node->directions_count = 0;
        node->i = queue_i;
        node->j = queue_j;
        node->frontiers = malloc(sizeof(FrontierDirection_t *) * 4);

        // printf("        Created a frontier node at:\n");
        // print_frontier_node(node);

        // printf("        Analyzing neighbours...\n");
        // === Check neighbours
        // Check the top neighbour
        check_neighbour(new_segment, map, matrix,
                        width, height, 
                        queue_i, queue_j,
                        node,
                        0, -1, TOP,
                        is_queue, js_queue, 
                        &queue_max_index);

        // Check the left neighbour
        check_neighbour(new_segment, map, matrix,
                        width, height, 
                        queue_i, queue_j,
                        node,
                        -1, 0, LEFT,
                        is_queue, js_queue, 
                        &queue_max_index);

        // Check the right neighbour
        check_neighbour(new_segment, map, matrix,
                        width, height, 
                        queue_i, queue_j,
                        node,
                        1, 0, RIGHT,
                        is_queue, js_queue, 
                        &queue_max_index);

        // Check the bottom neighbour
        check_neighbour(new_segment, map, matrix,
                        width, height, 
                        queue_i, queue_j,
                        node,
                        0, 1, DOWN,
                        is_queue, js_queue, 
                        &queue_max_index);

        // printf("        After analysis: \n");
        // print_frontier_node(node);

        // Check if node has == 0 directions. If so, delete node
        if (node->directions_count == 0) {
            // printf("        Node has 0 directions, so freeing it\n");
            free_frontier_node(node);
        } else {
            // printf("        Node has %d directions, so reallocating it\n", node->directions_count);
            node->frontiers = realloc(node->frontiers, sizeof(FrontierDirection_t *) * node->directions_count);

            new_segment->frontiers[new_segment->frontiers_count] = node;
            new_segment->frontiers_count += 1;
        }
    }
}

void create_map(Map_t *map, char *matrix, char width, char height, char possible_colors) {
    map->moves_count = 0;
    map->segment_count = 0;
    map->possible_colors = possible_colors;
    map->segments = malloc(sizeof(Segment_t *) * (width * height));

    int next_segment_id = 0;

    // List of verified nodes
    int check_size = 0;
    char *checked_is = malloc(sizeof(char) * width * height);
    char *checked_js = malloc(sizeof(char) * width * height);

    // Stack of nodes to check
    char *is_queue = malloc(sizeof(char) * width * height);
    char *js_queue = malloc(sizeof(char) * width * height);

    // TODO: Create segments and moves
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // printf("Checking i, j (%d, %d)\n", i, j);
            if (!has_checked_position(checked_is, checked_js, check_size, i, j)) {
                // Create a new segment
                Segment_t *new_segment = malloc(sizeof(Segment_t));

                new_segment->id = next_segment_id;
                
                next_segment_id += 1;

                new_segment->size = 0;
                new_segment->frontiers_count = 0;
                new_segment->frontiers = malloc(sizeof(FrontierNode_t *) * width * height);

                new_segment->gs_distance_to_initial = -1;
                new_segment->gs_distance_to_target = -1;
                new_segment->gs_factor = 0;
                new_segment->gs_visited = 0;

                new_segment->color = matrix[i * width + j];

                // printf("Created a new segment at %p in: \n", new_segment);
                // print_segment(new_segment);

                expand_segment(new_segment, map, matrix, 
                                checked_is, checked_js, &check_size,
                                width, height,
                                is_queue, js_queue,
                                i, j);

                // printf("Finished expanding. Segment now: \n");
                // print_segment(new_segment);

                // Reduce the size of the segments
                new_segment->frontiers = realloc(new_segment->frontiers, sizeof(FrontierNode_t *) * new_segment->frontiers_count);
                // printf("Reallocated segment.\n");

                // Add segment to segments
                map->segments[map->segment_count] = new_segment;
                map->segment_count += 1;
            }
        }
    }

    map->initial_segment = map->segments[0];

    // Reduce the size of the map
    map->segments = realloc(map->segments, sizeof(Segment_t *) * map->segment_count);

    // printf("Finished map. Map now: \n");
    // print_map(map);

    free(checked_is);
    free(checked_js);
    free(is_queue);
    free(js_queue);
}

Segment_t *find_segment_by_id(Map_t *map, int id) {
    for (int i = 0; i < map->segment_count; i++) {
        if (map->segments[i]->id == id) {
            return map->segments[i];
        }
    }
    return NULL;
}

Segment_t *find_largest_non_initial_segment(Map_t *map) {
    Segment_t *segment = NULL;
    int biggest_segment_size = 0;

    for (int k = 0; k < map->segment_count; k++) {
        if (map->segments[k]->size > biggest_segment_size && map->segments[k] != map->initial_segment) {
            segment = map->segments[k];
            biggest_segment_size = segment->size;
        }
    }

    return segment;
}

void clone_map(Map_t *dest, Map_t *original) {
    dest->possible_colors = original->possible_colors;

    dest->moves_count = original->moves_count;

    int moves_size = sizeof(char) * original->moves_count;
    dest->moves = malloc(moves_size);
    memcpy(dest->moves, original->moves, moves_size);

    dest->segment_count = original->segment_count;
    
    // printf("[clone_map] Cloned moves\n");

    // Clone segments
    dest->segments = malloc(sizeof(Segment_t *) * original->segment_count); 

    for (int i = 0; i < original->segment_count; i++) {
        Segment_t *clone = malloc(sizeof(Segment_t));
        clone_segment(clone, original->segments[i]);
        // printf("Cloned segment from ID %d to ID %d\n", original->segments[i]->id, clone->id);
        dest->segments[i] = clone;
    }

    // printf("[clone_map] Cloned segments\n");

    for (int i = 0; i < original->segment_count; i++) {
        if (dest->segments[i]->id == original->initial_segment->id) {
            dest->initial_segment = dest->segments[i];
            break;
        }
    }

    // Fix the frontier pointers
    for (int i = 0; i < original->segment_count; i++) {
        Segment_t *original_segment = original->segments[i];
        Segment_t *clone_segment = dest->segments[i];
        // printf("[clone_map] Original segment index %d has id %d\n", i, original_segment->id);
        // printf("[clone_map] Clone segment index %d has id %d\n", i, clone_segment->id);

        for (int j = 0; j < original_segment->frontiers_count; j++) {
            FrontierNode_t *original_frontier = original_segment->frontiers[j];
            FrontierNode_t *clone_frontier = clone_segment->frontiers[j];

            for (int k = 0; k < original_frontier->directions_count; k++) {
                FrontierDirection_t *original_direction = original_frontier->frontiers[k];
                FrontierDirection_t *clone_direction = clone_frontier->frontiers[k];

                // The direction segment ID
                int pointed_clone_segment_id = original_direction->pointed_node->parent_segment->id;

                // printf("    [clone_map] pointed_clone_segment_id: %d\n", pointed_clone_segment_id);

                Segment_t *pointed_clone_segment = find_segment_by_id(dest, pointed_clone_segment_id);

                // printf("    [clone_map] Search returned a pointer to %p", pointed_clone_segment);

                char original_pointed_i = original_direction->pointed_node->i;
                char original_pointed_j = original_direction->pointed_node->j;
                
                // printf("    [clone_map] Attempting to fix the node in (%d, %d)\n", original_pointed_i, original_pointed_j);

                // print_segment(pointed_clone_segment);

                FrontierNode_t *clone_pointed_node = find_node_by_position(pointed_clone_segment, original_pointed_i, original_pointed_j);
                // printf("    [clone_map] Found node at %p\n", clone_pointed_node);

                // Attribute to clone
                clone_direction->pointed_node = (struct FrontierNode_t *)clone_pointed_node;
            }
        }
    }

}

void paint_map(Map_t *dest, char color) {
    // printf("\n[paint_map] Attempting paint of map with %d. Initial segment has %d frontiers\n", color, dest->initial_segment->frontiers_count);
    
    // Add paint to the moves list
    // printf("[paint_map] Dest moves is %p\n", dest->moves);
    dest->moves = realloc(dest->moves, sizeof(char) * (dest->moves_count + 1));
    // printf("[paint_map] Dest moves after realloc is %p\n", dest->moves);
    dest->moves[dest->moves_count] = color;
    dest->moves_count += 1;

    // Actually paint the map
    Segment_t *initial_segment = dest->initial_segment;

    int added_segments = 0;
    Segment_t **buffer = malloc(sizeof(Segment_t *) * initial_segment->frontiers_count * 4);

    // Iterate each node's frontier and add the segment pointer to our buffer
    for (int k = 0; k < initial_segment->frontiers_count; k++) {
        FrontierNode_t *node = initial_segment->frontiers[k];

        // printf("[paint_map] Checking node in %d\n", k);
        // print_frontier_node(node);

        for (int t = 0; t < node->directions_count; t++) {
            FrontierDirection_t *dir = node->frontiers[t];

            // printf("[paint_map] Checking direction in %d\n", t);
            // print_frontier_direction(dir);

            // printf("[paint_map] Checking match! Segment %d has color %d\n", dir->pointed_node->parent_segment->id, dir->pointed_node->parent_segment->color);
            if (dir->pointed_node->parent_segment->color == color) {
                // printf("[paint_map] Matched! Adding it...\n");
                buffer[added_segments] = (Segment_t *)(dir->pointed_node->parent_segment);
                added_segments += 1;
            }
        }

    }

    // TODO: Remove later
    // printf("[paint_map] Before removing duplicates\n");
    for (int k = 0; k < added_segments; k++) {
        Segment_t *seg = buffer[k];
        if (seg != NULL) {
            // print_segment(seg);
        }
    }

    // Remove duplicates from the buffer
    for (int k = 0; k < added_segments; k++) {
        Segment_t *seg = buffer[k];

        if (seg == NULL) {
            continue;
        }

        // Check all positions forward
        for (int t = k + 1; t < added_segments; t++) {
            Segment_t *other_seg = buffer[t];

            if (seg == other_seg) {
                buffer[t] = NULL;
            }
        }
    }

    // TODO: Remove later
    // printf("[paint_map] After removing duplicates\n");
    for (int k = 0; k < added_segments; k++) {
        Segment_t *seg = buffer[k];
        if (seg != NULL) {
            // print_segment(seg);
        }
    }


    // For each segment that is not null in the buffer, merge with our inital segment
    // Remove duplicates from the buffer
    for (int k = 0; k < added_segments; k++) {
        Segment_t *seg = buffer[k];

        if (seg != NULL) {
            // printf("[paint_map] (K = %d) Attempting merge of segment %d with %d\n", k, initial_segment->id, seg->id);
            merge(initial_segment, seg);
            remove_segment_with_id(dest, seg->id);  
        }
    }

    free(buffer);
}

void print_map(Map_t *map) {
    printf("[print_map] Map [%p] moves: %d  / segments: %d\n", map, map->moves_count, map->segment_count);
}

void print_full_map(Map_t *map) {
    // printf("=================\n");
    print_map(map);

    for (int i = 0; i < map->segment_count; i++) {
        Segment_t *seg = map->segments[i];
        print_segment(seg);
        
        for (int j = 0; j < seg->frontiers_count; j++) {
            FrontierNode_t *node = seg->frontiers[j];
            print_frontier_node(node);

            for (int k = 0; k < node->directions_count; k++) {
                FrontierDirection_t *dir = node->frontiers[k];
                print_frontier_direction(dir);
            }
        }
    }
    // printf("=================\n");
}

void print_solution(Map_t *map) {
    printf("%d\n", map->moves_count);

    for (int i = 0; i < map->moves_count - 1; i++) {
        printf("%d ", map->moves[i]);
    }

    // Prints the last element
    if (map->moves_count > 0) {
        printf("%d\n", map->moves[map->moves_count - 1]);
    }
}

void remove_segment_with_id(Map_t *map, int id) {
    for (int i = 0; i < map->segment_count; i++) {
        if (map->segments[i]->id == id) {
            remove_segment(map, i);
            break;
        }
    }
}

void remove_segment(Map_t *map, int position) {
    // printf("[remove_segment] Called with position %d and map before:\n", position);
    
    Segment_t *segment = map->segments[position];
    free_segment(segment);

    // If it's not the last, update positions
    if (map->segment_count - 1 != position) {
        // printf("[remove_segment] Was not the last segment, so changing positions\n");
        // printf("========= Changing pos!\n");
        map->segments[position] = map->segments[map->segment_count - 1];
    } 

    map->segment_count -= 1;

    if (map->segment_count == 0) {
        // printf("========= Freeing frontier!\n");
        // printf("[remove_segment] No more segments so freeing it!\n");
        free(map->segments);
        map->segments = NULL;
    } else {
        // printf("[remove_segment] Reallocated the segment list to the new size!\n");
        map->segments = realloc(map->segments, sizeof(Segment_t *) * map->segment_count);
    }

    // printf("[remove_segment] Removed with position %d and map now:\n", position);
}

void free_map(Map_t *map) {
    for (int i = 0; i < map->segment_count; i++) {
        free_segment(map->segments[i]);
    }
    if (map->segments) {
        free(map->segments);
        map->segments = NULL;
    }
    if (map->moves) {
        free(map->moves);
        map->moves = NULL;
    }
    free(map);
}