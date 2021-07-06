#ifndef __UTILS_H_
#define __UTILS_H_

/* 
 * Returns the square of the distance between two points
 */ 
float point_squared_distance(char x_1, char y_1, char x_2, char y_2);

/* 
 * Reads the parameters from the stdin
 */ 
char read_parameters(char *width, char *height, char *colors_count);

/* 
 * Reads the map from the stdin. Assumes that the first line has already been read
 */ 
char read_map(char *map_dest, char line_count);

#endif