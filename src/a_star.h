#ifndef A_STAR_H
#define A_STAR_H

#include "priority_queue.h"

double heuristic_euclidean(int x1, int y1, int x2, int y2);
double heuristic_manhattan(int x1, int y1, int x2, int y2);
double calculate_heuristic(int x1, int y1, int x2, int y2, char *heuristic);
int a_star_solve(int rows, int cols, int **grid, int start_x, int start_y, int end_x, int end_y, char *heuristic);
void expand(int rows, int cols, int **grid, point curr_p, priority_queue *fringe);

#endif