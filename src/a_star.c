#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "priority_queue.h"

double heuristic_euclidean(int x1, int y1, int x2, int y2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

double heuristic_manhattan(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    return dx + dy;
}

int a_star_solve(int **grid, int start_x, int start_y, int end_x, int end_y, char *heuristic)
{
    if (strcmp(heuristic, "eucledian") != 0 && strcmp(heuristic, "manhattan") != 0)
    {
        printf("Invalid heuristic\n");
        exit(1);
    }
    printf("Heuristic: %s\n", heuristic);
    priority_queue *fringe = create_priority_queue(10);

    // Enqueue some points
    point p1 = {1, 2, 3.4};
    enqueue(fringe, p1);
}