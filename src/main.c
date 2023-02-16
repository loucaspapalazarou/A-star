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

    s = a_star_solve(rows, cols, grid, start_x, start_y, end_x, end_y, "eucledian");
    if (s != NULL)
    {
        printf("Solution from main. Time %f\n", s->time);
    }
    printf("\n");
    a_star_solve(rows, cols, grid, start_x, start_y, end_x, end_y, "manhattan");
    if (s != NULL)
    {
        printf("Solution from main. Time %f\n", s->time);
    }
    printf("\n");

    // produce solutions
    // write them to file

    return 0;
}