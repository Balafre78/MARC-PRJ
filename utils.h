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

//#define SEED 1730753576
#ifndef SEED
#include <time.h>
#endif

#define AMOUNT_MVT 7
#define ARR_MOVEPOOL { 22, 15, 7, 7, 21, 21, 7}
#define BASE_SUM 100

//#define DEBUG

/**
 * @brief Select movements for this turn
 * @param size amount of mvts to select
 * @return an array of move
 */
t_move *selMoves(int size);

/**
 * @brief Select movements for this turn
 * @param size amount of mvts to select
 * @return an array of move
 */
t_move *delMoves(int size);

/**
 * @brief Print a tree in console (stdout)
 * @param tree the tree to print
 */
void printTree(t_tree *tree);

#endif //MARC_PRJ_UTILS_H
