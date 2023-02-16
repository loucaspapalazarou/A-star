#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "priority_queue.h"
#include "utils.h"

#define MAX_PATH_LEN 100000

struct solution
{
    double time;
    int points_explored;
    point *end;
};

typedef struct solution solution;

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

void expand(int rows, int cols, int **grid, point *curr_p, int end_x, int end_y, priority_queue *fringe, char *heuristic, int **visited)
{
    int x = curr_p->x;
    int y = curr_p->y;
    if (grid[y][x] == 1)
    {
        printf("Invalid position\n");
        exit(1);
    }

    // check top
    if (y - 1 >= 0 && grid[y - 1][x] == 0 && visited[y - 1][x] == 0)
    {
        point *p1 = malloc(sizeof(point));
        visited[y - 1][x] = 1;
        double h = calculate_heuristic(x, y - 1, end_x, end_y, heuristic);
        p1->x = x;
        p1->y = y - 1;
        p1->cost = h + curr_p->cost + 1;
        p1->previous = curr_p;
        enqueue(fringe, p1);
    }
    // check botton
    if (y + 1 < rows && grid[y + 1][x] == 0 && visited[y + 1][x] == 0)
    {
        point *p2 = malloc(sizeof(point));
        visited[y + 1][x] = 1;
        double h = calculate_heuristic(x, y + 1, end_x, end_y, heuristic);
        p2->x = x;
        p2->y = y + 1;
        p2->cost = h + curr_p->cost + 1;
        p2->previous = curr_p;
        enqueue(fringe, p2);
    }
    // check left
    if (x - 1 >= 0 && grid[y][x - 1] == 0 && visited[y][x - 1] == 0)
    {
        point *p3 = malloc(sizeof(point));
        visited[y][x - 1] = 1;
        double h = calculate_heuristic(x - 1, y, end_x, end_y, heuristic);
        p3->x = x - 1;
        p3->y = y;
        p3->cost = h + curr_p->cost + 1;
        p3->previous = curr_p;
        enqueue(fringe, p3);
    }
    // check right
    if (x + 1 < cols && grid[y][x + 1] == 0 && visited[y][x + 1] == 0)
    {
        point *p4 = malloc(sizeof(point));
        visited[y][x + 1] = 1;
        double h = calculate_heuristic(x + 1, y, end_x, end_y, heuristic);
        p4->x = x + 1;
        p4->y = y;
        p4->cost = h + curr_p->cost + 1;
        p4->previous = curr_p;
        enqueue(fringe, p4);
    }
}

void trace_path(point *end, int start_x, int start_y)
{
    point *current = end;
    point *path[1000];
    int path_size = 0;

    while (current != NULL)
    {
        path[path_size++] = current;
        current = current->previous;
    }

    printf("Path length: %d\n", path_size - 1);
    printf("Path [");
    for (int i = path_size - 1; i >= 0; i--)
    {
        printf("(%d, %d)", path[i]->y, path[i]->x);
        if (i != 0)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

solution *a_star_solve(int rows, int cols, int **grid, int start_x, int start_y, int end_x, int end_y, char *heuristic)
{
    if (strcmp(heuristic, "eucledian") != 0 && strcmp(heuristic, "manhattan") != 0)
    {
        printf("Invalid heuristic\n");
        return NULL;
    }
    printf("Starting with %s heuristic\n", heuristic);

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

    point *start = malloc(sizeof(point));
    solution *sol = malloc(sizeof(solution));
    start->x = start_x;
    start->y = start_y;
    start->cost = 0;
    start->previous = NULL;
    enqueue(fringe, start);
    visited[start_y][start_x] = 1;
    int explored_points = 1;
    clock_t start_time, end_time;
    double elapsed_time;

    start_time = clock();
    while (!is_empty(fringe))
    {
        point *point_to_expand = dequeue(fringe);
        explored_points++;

        if (point_to_expand->x == end_x && point_to_expand->y == end_y)
        {
            end_time = clock();
            sol->points_explored = explored_points;
            elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            sol->time = elapsed_time;
            // trace_path(point_to_expand, start_x, start_y);
            destroy_priority_queue(fringe);
            for (int i = 0; i < rows; i++)
            {
                free(visited[i]);
            }
            free(visited);
            free(start);

            // RETURN SOLUTION OBJECT
            return sol;
        }

        expand(rows, cols, grid, point_to_expand, end_x, end_y, fringe, heuristic, visited);
    }
    printf("No path found\n");
    printf("Explored %d points\n", explored_points);
    destroy_priority_queue(fringe);
    for (int i = 0; i < rows; i++)
    {
        free(visited[i]);
    }
    free(visited);
    free(start);
    return NULL;
}