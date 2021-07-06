#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define MAX_PARAMETERS_BUFFER_SIZE 15

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
    }

    // Get the width
    *width = atoi(pch);

    pch = strtok(NULL, " ");
    if (pch == NULL) {
        // TODO: Gracefully fail
    }

    // Get the height
    *height = atoi(pch);

    pch = strtok(NULL, " ");
    if (pch == NULL) {
        // TODO: Gracefully fail
    }

    // Get the colors count
    *colors_count = atoi(pch);

    return 0;
}

char read_map(char *map_dest) {

}