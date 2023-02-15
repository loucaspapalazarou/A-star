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

void expand(int rows, int cols, int **grid, point curr_p, priority_queue *fringe)
{
    int x = curr_p.x;
    int y = curr_p.y;
    if (grid[y][x] == 1)
    {
        printf("Invalid position\n");
        exit(1);
    }
    // check top
    if (y - 1 >= 0 && grid[y - 1][x] == 0)
    {
        point p = {x, y - 1, 0};
        enqueue(fringe, p);
    }
    // botton
    if (y + 1 < rows && grid[y + 1][x] == 0)
    {
        point p = {x, y + 1, 0};
        enqueue(fringe, p);
    }
    // left
    if (x - 1 >= 0 && grid[y][x - 1] == 0)
    {
        point p = {x - 1, y, 0};
        enqueue(fringe, p);
    }
    // right
    if (x + 1 < cols && grid[y][x + 1] == 0)
    {
        point p = {x + 1, y, 0};
        enqueue(fringe, p);
    }
}

int a_star_solve(int rows, int cols, int **grid, int start_x, int start_y, int end_x, int end_y, char *heuristic)
{
    if (strcmp(heuristic, "eucledian") != 0 && strcmp(heuristic, "manhattan") != 0)
    {
        printf("Invalid heuristic\n");
        exit(1);
    }
    printf("Heuristic: %s\n", heuristic);
    priority_queue *fringe = create_priority_queue(10);

    point start = {start_x, start_y, 0};
    enqueue(fringe, start);

    if (start_x == end_x && start_y == end_y)
    {
        printf("Path found!\n");
        return 1;
    }

    point point_to_expand = dequeue(fringe);

    expand(rows, cols, grid, point_to_expand, fringe);

    print_priority_queue(fringe);
}