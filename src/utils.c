#include <stdio.h>
#include <stdlib.h>

#include "a_star.h"

void read_file(const char *filename, int *rows, int *cols, int ***grid, int *start_x, int *start_y, int *end_x, int *end_y)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    fscanf(file, "%d %d", rows, cols);
    int i, j;
    *grid = (int **)malloc(*rows * sizeof(int *));
    for (i = 0; i < *rows; i++)
    {
        (*grid)[i] = (int *)malloc(*cols * sizeof(int));
        for (j = 0; j < *cols; j++)
        {
            fscanf(file, "%1d", &(*grid)[i][j]);
        }
    }

    fscanf(file, "%d %d %d %d", start_y, start_x, end_y, end_x);

    fclose(file);
}

void print_grid(int rows, int cols, int **grid)
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%d", grid[i][j]);
        }
        printf("\n");
    }
}

void append_solution_to_csv(int rows, int cols, solution *s1, solution *s2)
{
    char filename[100];
    sprintf(filename, "results.csv");

    FILE *f = fopen(filename, "a"); // open the file in append mode
    if (f == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    // write the headers to the file if it does not exist
    if (ftell(f) == 0)
    {
        fprintf(f, "size,time-eucledian,points-explored-eucledian,time-manhattan,points-explored-manhattan\n");
    }

    // write the fields of the solution struct to the file
    fprintf(f, "%dx%d,%.6f,%d,", rows, cols, s1->time, s1->points_explored);
    fprintf(f, "%.6f,%d\n", s2->time, s2->points_explored);

    fclose(f); // close the file
}
