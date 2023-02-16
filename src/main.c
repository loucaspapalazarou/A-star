#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "a_star.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Wrong amount of arguments");
        exit(1);
    }

    int rows, cols;
    int **grid;
    int start_x, start_y, end_x, end_y;
    read_file(argv[1], &rows, &cols, &grid, &start_x, &start_y, &end_x, &end_y);

    solution *s;

    s = a_star_solve(rows, cols, grid, start_x, start_y, end_x, end_y, "eucledian", 1);
    if (s != NULL)
    {
        printf("Path found in %fs\n", s->time);
        printf("Explored %d points\n", s->points_explored);
    }
    printf("\n");
    a_star_solve(rows, cols, grid, start_x, start_y, end_x, end_y, "manhattan", 0);
    if (s != NULL)
    {
        printf("Solution from main. Time %f\n", s->time);
    }
    printf("\n");

    // produce solutions
    // write them to file

    return 0;
}