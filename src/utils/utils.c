float point_squared_distance(short x_1, short y_1, short x_2, short y_2) {
    short x = x_2 - x_1;
    short y = y_2 - y_1;
    return (x * x) + (y * y);
}