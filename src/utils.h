#ifndef UTILS_H
#define UTILS_H

#include "priority_queue.h"

typedef struct solution solution;

void read_file(const char *filename, int *rows, int *cols, int ***matrix, int *start_x, int *start_y, int *end_x, int *end_y);
void print_grid(int rows, int cols, int **grid);
void append_solution_to_csv(int rows, int cols, solution *s1, solution *s2);

#endif