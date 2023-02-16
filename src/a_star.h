#ifndef A_STAR_H
#define A_STAR_H

#include "priority_queue.h"
#include "utils.h"

struct solution
{
    double time;
    int points_explored;
    point *end;
};

typedef struct solution solution;

double heuristic_euclidean(int x1, int y1, int x2, int y2);
double heuristic_manhattan(int x1, int y1, int x2, int y2);
double calculate_heuristic(int x1, int y1, int x2, int y2, char *heuristic);
solution *a_star_solve(int rows, int cols, int **grid, int start_x, int start_y, int end_x, int end_y, char *heuristic);
void expand(int rows, int cols, int **grid, point *curr_p, int end_x, int end_y, priority_queue *fringe, char *heuristic, int **visited);
void trace_path(point *end, int start_x, int start_y);

#endif