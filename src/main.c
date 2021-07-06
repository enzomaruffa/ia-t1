#include <stdlib.h>
#include <stdio.h>
#include "map.h"
#include "utils/utils.h"

int main() {
    char width;
    char height;
    char colors_count;

    read_parameters(&width, &height, &colors_count);

    printf("width: %d\n", width);
    printf("height: %d\n", height);
    printf("colors: %d\n", colors_count);

    int total_cells = width * height;

    // Allocate necessary space - should not fail
    short *map_cells = malloc(sizeof(char) * total_cells);

    return 0;
}