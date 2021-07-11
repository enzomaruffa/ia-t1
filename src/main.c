#include <stdlib.h>
#include <stdio.h>
#include "map.h"
#include "utils/utils.h"

int main() {
    char width;
    char height;
    char colors_count;

    read_parameters(&width, &height, &colors_count);

    int total_cells = width * height;

    // Allocate necessary space - should not fail
    char *map_cells = malloc(sizeof(char) * total_cells);
    read_map(map_cells, height);

    Map_t *map = malloc(sizeof(Map_t));
    create_map(map, map_cells, width, height);

    printf("=================\n");
    printf("======== MAP ==\n");
    print_map(map);

    for (int i = 0; i < map->segment_count; i++) {
        printf("    ===== SEGMENT ==\n");
        Segment_t *seg = map->segments[i];
        print_segment(seg);
        
        for (int j = 0; j < seg->frontiers_count; j++) {
            printf("        === FRONTIER NODE ==\n");
            FrontierNode_t *node = seg->frontiers[j];
            print_frontier_node(node);

            for (int k = 0; k < node->directions_count; k++) {
                printf("                = FRONTIER DIRECTION ==\n");
                FrontierDirection_t *dir = node->frontiers[k];
                print_frontier_direction(dir);
            }
        }
    }

    free_map(map);

    return 0;
}