//
// Created by pierr on 17/11/2024.
//

#include "slope.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "map.h"
#include "loc.h"
#include "queue.h"


void createSlopeArrFromFile(t_map map, char *filename) {
    /* rules for the file :
     * - the first line contains the number of lines : y dimension (int)
     * - the second line contains the number of columns : x dimension (int)
     * - the next lines contain the slope values (int) separated by spaces : one line = one row
     * - the values are the following : 0 = NO_SLOPE, 1 = S_RIGHT, 2 = S_UP, 3 = S_LEFT, 4 = S_DOWN
     */

    int xdim, ydim;     // dimensions of the map
    char buff[100];


    // filename + .slope (+6)
    char *fullFilename = (char *) malloc((strlen(filename) + 6 + 1) * sizeof(char));
    if (fullFilename == NULL) {
        fprintf(stderr, "Cannot allocate mem!\n");
        exit(EXIT_FAILURE);
    }
    strcpy(fullFilename, filename);
    strcat(fullFilename, ".slope");
    printf("%s\n", fullFilename);

    FILE *file = fopen(fullFilename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: cannot open file %s\n", filename);
        exit(1);
    }

    fscanf(file, "%d", &ydim);
    fscanf(file, "%d", &xdim);
    if (ydim != map.y_max || xdim != map.x_max) {
        fprintf(stderr, "Incoherent slope dimension descriptor !\n");
        free(fullFilename);
        exit(1);
    }

    map.slopes = (t_slopeOrientation **) malloc(ydim * sizeof(t_slopeOrientation *));
    for (int i = 0; i < ydim; i++) {
        map.slopes[i] = (t_slopeOrientation *) malloc(xdim * sizeof(t_slopeOrientation));
    }

    int buffptr = -1;

    do {
        // Read single character from file
        buff[buffptr + 1] = fgetc(file);
        buffptr++;
        printf("%c", buff[buffptr]);
    } while(buff[buffptr] != '\n' && buff[buffptr] != ' ');
    buffptr = -1;

    int value;
    for (int i = 0; i < ydim; i++) {
        // parse the line to get the values : 0 = NO_SLOPE, 1 = S_RIGHT, 2 = S_UP, 3 = S_LEFT, 4 = S_DOWN
        // values are separated by spaces, so we use sscanf with %d to get the values
        for (int j = 0; j < xdim; j++) {
            // fscanf is locked on the last digit of the first line
            //printf("(%2d)--", fscanf(file, "%d", &value));
            do {
                // Read single character from file
                buff[buffptr + 1] = fgetc(file);
                buffptr++;
                printf("%c", buff[buffptr]);
                if (buff[buffptr] == EOF) {
                    printf("%d %d\n", ferror(file), feof(file));
                    perror("Err");
                    exit(1);
                }
            } while(buff[buffptr] != '\n' && buff[buffptr] != ' ');
            buff[buffptr] = '\0';
            buffptr = -1;

            sscanf(buff, "%d", &value);

            map.slopes[i][j] = value;
            printf("%d@(%d,%d)\n", value, j, i);
            switch (value) {
                case S_RIGHT:
                    if (isValidLocalisation((t_position) {j + 1, i}, map.x_max, map.y_max))
                        map.costs[i][j] = map.costs[i][j + 1];
                    else
                        map.costs[i][j] = COST_DIE;
                    break;
                case S_UP:
                    if (isValidLocalisation((t_position) {j, i - 1}, map.x_max, map.y_max))
                        map.costs[i][j] = map.costs[i - 1][j];
                    else
                        map.costs[i][j] = COST_DIE;
                    break;
                case S_LEFT:
                    if (isValidLocalisation((t_position) {j - 1, i}, map.x_max, map.y_max))
                        map.costs[i][j] = map.costs[i][j - 1];
                    else
                        map.costs[i][j] = COST_DIE;
                    break;
                case S_DOWN:
                    if (isValidLocalisation((t_position) {j, i + 1}, map.x_max, map.y_max))
                        map.costs[i][j] = map.costs[i + 1][j];
                    else
                        map.costs[i][j] = COST_DIE;
                    break;
            }

        }
        fclose(file);
        //free(fullFilename);
    }
}