//
// Created by pierr on 17/11/2024.
//

#include "slope.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "map.h"
#include "loc.h"


void createSlopeArrFromFile(t_map *map, char *filename) {
    /* rules for the file :
     * - the first line contains the number of lines : y dimension (int)
     * - the second line contains the number of columns : x dimension (int)
     * - the next lines contain the slope values (int) separated by spaces : one line = one row
     * - the values are the following : 0 = NO_SLOPE, 1 = S_RIGHT, 2 = S_UP, 3 = S_LEFT, 4 = S_DOWN
     */

    int xdim, ydim;     // dimensions of the map
    //char buff[100];


    // filename + .slope (+6)
    char *fullFilename = (char *) malloc((strlen(filename) + 6 + 1) * sizeof(char));
    if (fullFilename == NULL) {
        fprintf(stderr, "Cannot allocate mem!\n");
        exit(EXIT_FAILURE);
    }
    strcpy(fullFilename, filename);
    strcat(fullFilename, ".slope");

    FILE *file = fopen(fullFilename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: cannot open file %s\n", filename);
        fprintf(stderr,
                "NB: To use SLOPE_OPT you must have a corresponding .slope file in the same directory as your .map");
        exit(1);
    }

    fscanf(file, "%d", &ydim);
    fscanf(file, "%d", &xdim);
    printf("dims: %d %d\n", ydim, xdim);
    if (ydim != map->y_max || xdim != map->x_max) {
        fprintf(stderr, "Incoherent slope dimension descriptor !\n");
        free(fullFilename);
        exit(1);
    }

    map->slopes = (t_slopeOrientation **) malloc(ydim * sizeof(t_slopeOrientation *));
    int **altcosts = (int **) malloc(ydim * sizeof(int *));
    if (altcosts == NULL || map->slopes == NULL) {
        fprintf(stderr, "Cannot allocate mem!");
        exit(1);
    }
    for (int i = 0; i < ydim; i++) {
        map->slopes[i] = (t_slopeOrientation *) malloc(xdim * sizeof(t_slopeOrientation));
        altcosts[i] = (int *) malloc(xdim * sizeof(int));
        if (altcosts[i] == NULL || map->slopes[i] == NULL) {
            fprintf(stderr, "Cannot allocate mem!");
            exit(1);
        }
    }


    int value;
    for (int i = 0; i < ydim; i++) {
        // parse the line to get the values : 0 = NO_SLOPE, 1 = S_RIGHT, 2 = S_UP, 3 = S_LEFT, 4 = S_DOWN
        // values are separated by spaces, so we use sscanf with %d to get the values
        for (int j = 0; j < xdim; j++) {

            fscanf(file, "%d", &value);

            //printf(" %d", value);

            map->slopes[i][j] = value;
            switch (value) {
                case S_RIGHT:
                    if (isValidLocalisation((t_position) {j + 1, i}, map->x_max, map->y_max))
                        altcosts[i][j] = map->costs[i][j + 1];
                    else
                        altcosts[i][j] = COST_DIE;
                    break;
                case S_UP:
                    if (isValidLocalisation((t_position) {j, i - 1}, map->x_max, map->y_max))
                        altcosts[i][j] = map->costs[i - 1][j];
                    else
                        altcosts[i][j] = COST_DIE;
                    break;
                case S_LEFT:
                    if (isValidLocalisation((t_position) {j - 1, i}, map->x_max, map->y_max))
                        altcosts[i][j] = map->costs[i][j - 1];
                    else
                        altcosts[i][j] = COST_DIE;
                    break;
                case S_DOWN:
                    if (isValidLocalisation((t_position) {j, i + 1}, map->x_max, map->y_max))
                        altcosts[i][j] = map->costs[i + 1][j];
                    else
                        altcosts[i][j] = COST_DIE;
                    break;
                case NO_SLOPE:
                    altcosts[i][j] = map->costs[i][j];
                    break;
                default:
                    fprintf(stderr, "Incorrect slope value !");
                    exit(1);
            }

        }

        //printf("\n");
    }

    fclose(file);

    // Transfer altcosts ownership to costs so free previous costs
    for (int i = 0; i < ydim; i++) {
        free(map->costs[i]);
    }
    free(map->costs);
    map->costs = altcosts;

    /*for (int i = 0; i < ydim; i++) {
        for (int j = 0; j < xdim; j++)
            printf(" %5d", map->costs[i][j]);
        printf("\n");
    }
    for (int i = 0; i < ydim; i++) {
        for (int j = 0; j < xdim; j++)
            printf(" %5d", map->slopes[i][j]);
        printf("\n");
    }
    for (int i = 0; i < ydim; i++) {
        for (int j = 0; j < xdim; j++)
            printf(" %5d", map->soils[i][j]);
        printf("\n");
    }*/

}