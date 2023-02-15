#ifndef A_STAR_H
#define A_STAR_H

double heuristic_euclidean(int x1, int y1, int x2, int y2);
double heuristic_manhattan(int x1, int y1, int x2, int y2);
int a_star_solve(int **grid, int start_x, int start_y, int end_x, int end_y, char *heuristic);

#endif