#ifndef UTILS_H
#define UTILS_H

void read_file(const char *filename, int *rows, int *cols, int ***matrix, int *start_x, int *start_y, int *end_x, int *end_y);
void print_grid(int rows, int cols, int **grid);

#endif