//
// Created by pierr on 23/10/2024.
//

#ifndef MARC_PRJ_UTILS_H
#define MARC_PRJ_UTILS_H

#include "moves.h"
#include "tree.h"

/**
 * @brief Select movements for this turn
 * @param size amount of mvts to select
 * @return an array of move
 */
t_move *selMoves(int size);

/**
 * @brief Print a tree in console (stdout)
 * @param tree the tree to print
 */
void printTree(t_tree *tree);

#endif //MARC_PRJ_UTILS_H
