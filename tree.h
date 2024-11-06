//
// Created by pierr on 23/10/2024.
//

#ifndef MARC_PRJ_TREE_H
#define MARC_PRJ_TREE_H

#include <stdlib.h>
#include <stdio.h>

#include "moves.h"
#include "map.h"
#include "stack.h"
#include "queue.h"
#include "utils.h"


typedef struct s_node {
    int value;            // Final point reached in value
    int depth;            // Depth of the tree
    int nbSons;           // Amount of sons
    struct s_node **sons; // Link to sons ALWAYS SORTED IN RIGHT ORDER
} t_node;

typedef struct s_tree {
    t_node *root;       // Root of the tree
    int lenArr;         // length of the moveSet
    t_move *moveArr;    // Define all moves in the tree
    int maxDepth;       // Max depth of the tree
} t_tree;


/*

    ________                      ___
   / ____/ /_____ _____  ___     <  /
  / __/ / __/ __ `/ __ \/ _ \    / /
 / /___/ /_/ /_/ / /_/ /  __/   / /
/_____/\__/\__,_/ .___/\___/   /_/
               /_/
 * Etape 1

*/


/**
 * @brief Create a node in the heap
 * @param value Value of node
 * @param depth Depth of node from root of the tree
 * @param nbSons Amount of sons to populate
 * @return Pointer to the node
 */
t_node *createNode(int value, int depth, int nbSons);

/**
 * @brief Destroy a node in the heap
 * @param node The node to delete
 */
void deleteNode(t_node *node);

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
void deleteTree(t_node *tree);

/**
 * @brief Find the minimal value in Tree
 * @param tree The tree to look into
 * @return The minimal node
 */
t_node *minimalNode(t_tree tree);

/**
 * @brief Find a node in a tree
 * This function will use POSTFIX SEARCH (find leaves first) ??? not sure
 * @param node the Node
 * @param tree the Tree
 * @return a stack from root to the given node (on top)
 */
t_stack findNodePath(t_node *node, t_tree tree);


/*
   ____  ____  ______    _____   __
  / __ \/ __ \/_  __/   /  _/ | / /
 / / / / /_/ / / /_____ / //  |/ /
/ /_/ / ____/ / /_____// // /|  /
\____/_/     /_/     /___/_/ |_/

 * OPT-IN

*/


/**
 * @brief Build the minimal tree
 * @param map Map to analyse
 * @param maxDepth Amount of mvts to use
 * @param lenArr Length of the moveArr
 * @param moveArr Array of mvts available
 * @return Pointer to the Tree
 */
t_tree *buildMinimalTree(t_map map, int maxDepth, int lenArr, t_move *moveArr);

/**
 * @brief Build the combinatory tree, implement slope
 * @param map Map to analyse
 * @param maxDepth Amount of mvts to use
 * @param lenArr Length of the moveArr
 * @param moveArr Array of mvts available
 * @return Pointer to the Tree
 */
t_tree *buildSlopeTree(t_map map, int maxDepth, int lenArr, t_move *moveArr);

/**
 * @brief Build the minimal tree, implement slope
 * @param map Map to analyse
 * @param maxDepth Amount of mvts to use
 * @param lenArr Length of the moveArr
 * @param moveArr Array of mvts available
 * @return Pointer to the Tree
 */
t_tree *buildMinimalSlopeTree(t_map map, int maxDepth, int lenArr, t_move *moveArr);

#endif //MARC_PRJ_TREE_H
