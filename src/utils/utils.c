#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

// 3 char for each dimension, 2 for the color count. Extra 5.
#define MAX_PARAMETERS_BUFFER_SIZE 15

// 3 for each char, 100 chars. Extra 5.
#define MAX_MAP_LINE_BUFFER_SIZE 305

float point_squared_distance(char x_1, char y_1, char x_2, char y_2) {
    char x = x_2 - x_1;
    char y = y_2 - y_1;
    return (x * x) + (y * y);
}

char read_parameters(char *width, char *height, char *colors_count) {
    char buffer[MAX_PARAMETERS_BUFFER_SIZE];
    fgets(buffer, MAX_PARAMETERS_BUFFER_SIZE, stdin);
    
    char *pch;
    pch = strtok(buffer, " ");
    if (pch == NULL) {
        // TODO: Gracefully fail
        return 1;
    }

    // Get the height
    *height = atoi(pch);

    pch = strtok(NULL, " ");
    if (pch == NULL) {
        // TODO: Gracefully fail
        return 1;
    }

    // Get the width
    *width = atoi(pch);

    pch = strtok(NULL, " ");
    if (pch == NULL) {
        // TODO: Gracefully fail
        return 1;
    }

    // Get the colors count
    *colors_count = atoi(pch);

    return 0;
}

char read_map(char *map_dest, char line_count) {
    char buffer[MAX_MAP_LINE_BUFFER_SIZE];
    fgets(buffer, MAX_MAP_LINE_BUFFER_SIZE, stdin);
    char *pch;

    int total_lines_read = 0;
    int total_read = 0;

    while (total_lines_read < line_count) {
        pch = strtok(buffer, " ");

        while (pch != NULL) {
            map_dest[total_read] = atoi(pch);
            total_read += 1;

            pch = strtok(NULL, " ");
        }   

        fgets(buffer, MAX_MAP_LINE_BUFFER_SIZE, stdin);
        total_lines_read += 1;
    }

    return 0;
}