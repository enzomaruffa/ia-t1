#include <stdlib.h>
#include <stdio.h>
#include "../types/map.h"
#include "most_distant_segment.h"
#include "biggest_resulting_segment.h"

void solve(Map_t *map) {
    if (map->segment_count > 200) {
        printf("Map has %d segments, so solving by the most distant\n", map->segment_count);
        solve_most_distant_segment(map, 20, 200);
        printf("Reduced to %d!\n", map->segment_count);
    }

    if (map->segment_count >= 80) {
        int factor = 3;
        printf("Map has %d segments, so solving using biggest with factor %d\n", map->segment_count, factor);
        solve_biggest_resulting_segment(map, factor, 80);
    }

    if (map->segment_count >= 30) {
        int factor = 5;
        printf("Map has %d segments, so solving using biggest with factor %d\n", map->segment_count, factor);
        solve_biggest_resulting_segment(map, factor, 30);
    }

    int factor = 8;
    printf("Map has %d segments, so solving using biggest with factor %d\n", map->segment_count, factor);
    solve_biggest_resulting_segment(map, factor, 1);
}