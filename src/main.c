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
    // print_grid(rows, cols, grid);

    a_star_solve(grid, start_x, start_y, end_x, end_y, "eucledian");

    return 0;
}