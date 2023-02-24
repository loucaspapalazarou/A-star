#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "a_star.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Wrong amount of arguments\n");
        exit(1);
    }

    int rows, cols;
    int **grid;
    int start_x, start_y, end_x, end_y;
    read_file(argv[1], &rows, &cols, &grid, &start_x, &start_y, &end_x, &end_y);

    solution *s_euc, *s_manh;

    s_euc = a_star_solve(rows, cols, grid, start_x, start_y, end_x, end_y, "eucledian", 1);
    if (s_euc != NULL)
    {
        printf("Path found in %fs\n", s_euc->time);
        printf("Explored %d points\n", s_euc->points_explored);
    }
    printf("\n");
    s_manh = a_star_solve(rows, cols, grid, start_x, start_y, end_x, end_y, "manhattan", 1);
    if (s_manh != NULL)
    {
        printf("Path found in %fs\n", s_manh->time);
        printf("Explored %d points\n", s_manh->points_explored);
    }
    printf("\n");

    append_solution_to_csv(rows, cols, s_euc->time, s_euc->points_explored, s_manh->time, s_manh->points_explored);

    return 0;
}