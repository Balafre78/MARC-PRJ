//
// Created by pierr on 23/10/2024.
//

#ifndef MARC_PRJ_TREE_H
#define MARC_PRJ_TREE_H

#include <stdlib.h>
#include <stdio.h>

#include "map.h"
#include "stack.h"
#include "node.h"
#include "moves.h"


typedef struct s_tree {
    t_node *root;       // Root of the tree
    int lenArr;         // length of the moveSet
    t_move *moveArr;    // Define all moves in the tree
    int maxDepth;       // Max depth of the tree
} t_tree;

/**
 * @brief Build the combinatory tree
 * @param map Map to analyse
 * @param maxDepth Amount of mvts to use
 * @param lenArr Length of the moveArr
 * @param moveArr Array of mvts available
 * @param iniLoc Initial location of the robot
 * @return Pointer to the Tree
 */
t_tree *buildTree(t_map map, int maxDepth, int lenArr, t_move *moveArr, t_localisation iniLoc);

/**
 * @brief Destroy a Tree in the heap
 * @param tree The tree to delete
 */
void deleteTree(t_tree *tree);

/**
 * @brief Find the minimal value in Tree
 * @param tree The tree to look into
 * @return The minimal node
 */
t_node *minimalNode(t_tree tree);

/**
 * @brief Find a node in a tree
 * @param node the Node
 * @param tree the Tree
 * @return a stack from root to the given node (on top)
 */
t_stack findNodePath(t_node *node, t_tree tree);

#endif //MARC_PRJ_TREE_H
