//
// Created by pierr on 17/11/2024.
//

#ifndef MARC_PRJ_SLOPE_H
#define MARC_PRJ_SLOPE_H

typedef struct s_map t_map;

typedef enum e_slopeOrientation {
    NO_SLOPE,
    S_RIGHT,
    S_UP,
    S_LEFT,
    S_DOWN
} t_slopeOrientation;

/**
 * @brief Function to initialise the slope map and costs from a file (+check integrity) and the map
 * @param map : the map to fill
 * @param filename : the name of the file
 * @return the map
 */
void createSlopeArrFromFile(t_map map, char *filename);


#endif //MARC_PRJ_SLOPE_H
