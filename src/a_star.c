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

double calculate_heuristic(int x1, int y1, int x2, int y2, char *heuristic)
{
    if (strcmp(heuristic, "eucledian") != 0 && strcmp(heuristic, "manhattan") != 0)
    {
        printf("Invalid heuristic\n");
        exit(1);
    }
    if (strcmp(heuristic, "eucledian") == 0)
    {
        return heuristic_euclidean(x1, y1, x2, y2);
    }
    if (strcmp(heuristic, "manhattan") == 0)
    {
        return heuristic_manhattan(x1, y1, x2, y2);
    }
}

void expand(int rows, int cols, int **grid, point curr_p, int end_x, int end_y, priority_queue *fringe, char *heuristic, int **visited)
{
    int x = curr_p.x;
    int y = curr_p.y;
    if (grid[y][x] == 1)
    {
        printf("Invalid position\n");
        exit(1);
    }
    // check top
    if (y - 1 >= 0 && grid[y - 1][x] == 0 && visited[y - 1][x] == 0)
    {
        double h = calculate_heuristic(x, y - 1, end_x, end_y, heuristic);
        double last_cost = curr_p.cost;
        point p = {x, y - 1, h + last_cost + 1};
        visited[y - 1][x] = 1;
        enqueue(fringe, p);
    }
    // check botton
    if (y + 1 < rows && grid[y + 1][x] == 0 && visited[y + 1][x] == 0)
    {
        double h = calculate_heuristic(x, y + 1, end_x, end_y, heuristic);
        double last_cost = curr_p.cost;
        point p = {x, y + 1, h + last_cost + 1};
        visited[y + 1][x] = 1;
        enqueue(fringe, p);
    }
    // check left
    if (x - 1 >= 0 && grid[y][x - 1] == 0 && visited[y][x - 1] == 0)
    {
        double h = calculate_heuristic(x - 1, y, end_x, end_y, heuristic);
        double last_cost = curr_p.cost;
        point p = {x - 1, y, h + last_cost + 1};
        visited[y][x - 1] = 1;
        enqueue(fringe, p);
    }
    // check right
    if (x + 1 < cols && grid[y][x + 1] == 0 && visited[y][x + 1] == 0)
    {
        double h = calculate_heuristic(x + 1, y, end_x, end_y, heuristic);
        double last_cost = curr_p.cost;
        point p = {x + 1, y, h + last_cost + 1};
        visited[y][x + 1] = 1;
        enqueue(fringe, p);
    }
}

// void print_path()
// {
// }

int a_star_solve(int rows, int cols, int **grid, int start_x, int start_y, int end_x, int end_y, char *heuristic)
{
    if (strcmp(heuristic, "eucledian") != 0 && strcmp(heuristic, "manhattan") != 0)
    {
        printf("Invalid heuristic\n");
        exit(1);
    }

    priority_queue *fringe = create_priority_queue(rows * cols);

    int **visited = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        visited[i] = (int *)malloc(cols * sizeof(int));
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            visited[i][j] = 0;
        }
    }

    point start = {start_x, start_y, 0};
    enqueue(fringe, start);
    visited[start_y][start_x] = 1;

    // IF SOLUTION IS FOUND, USE PREVIOUS FROM POINT TO TRACK DOWN THE PATH
    while (!is_empty(fringe))
    {
        point point_to_expand = dequeue(fringe);
        // printf("Extracted (%d, %d)\n", point_to_expand.x, point_to_expand.y);

        if (point_to_expand.x == end_x && point_to_expand.y == end_y)
        {
            printf("Path found!\n");
            // print_path();
            return 1;
        }
        expand(rows, cols, grid, point_to_expand, end_x, end_y, fringe, heuristic, visited);
    }
    printf("No path found\n");
    return 0;
}