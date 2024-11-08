//
// Created by pierr on 23/10/2024.
//

#ifndef MARC_PRJ_UTILS_H
#define MARC_PRJ_UTILS_H

#include <stdlib.h>

#include "moves.h"
#include "tree.h"

typedef struct s_tree t_tree;

#define COST_DIE 1000

// Define the seed either with predefined SEED macro or with some randomness
// Decomment SEED macro to use fix seed for random generation
//#define SEED 1730810125
#ifndef SEED
#include <time.h>
#endif

// Define with macro how to describe the base distribution of moves.
#define AMOUNT_MVT 7
#define ARR_MOVEPOOL { 22, 15, 7, 7, 21, 21, 7}
#define BASE_SUM 100

// Debug flag macro - help for debugging stuff
//#define DEBUG

/**
 * @brief Select movements for this turn
 * @param size amount of mvts to select
 * @return an array of move
 */
t_move *selMoves(int size);

/**
 * @brief Delete movement array
 * @param moveArr the movement array
 */
void delMoves(t_move *moveArr);

/**
 * @brief function to update the localisation of the robot according to a move
 * @warning this function is based on the fact the robot starts to move on erg
 * @param loc : the localisation of the robot
 * @param move : the move to do
 * @return the new localisation of the robot
 */
t_localisation ergMove(t_localisation, t_move);

/**
 * @brief Print a tree in console (stdout)
 * @param tree the tree to print
 */
void printTree(t_tree *tree);

#endif //MARC_PRJ_UTILS_H
