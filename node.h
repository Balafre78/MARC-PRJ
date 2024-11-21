//
// Created by Raphy on 12/11/2024.
//

#ifndef MARC_PRJ_NODE_H
#define MARC_PRJ_NODE_H
#include "moves.h"

typedef struct s_node {
    int value;             // Final point reached in value
    int depth;             // Depth of the tree
    int nbSons;            // Amount of sons
    struct s_node **sons;  // Link to sons ALWAYS SORTED IN RIGHT ORDER
    struct s_node *parent; // Parent node - NULL for root
} t_node;

/**
 * @brief Create a node in the heap
 * @param value Value of node
 * @param depth Depth of node from root of the tree
 * @param nbSons Amount of sons to populate
 * @param parent Parent of the node
 * @return Pointer to the node
 */
t_node *createNode(int value, int depth, int nbSons, t_node *parent);



#endif //MARC_PRJ_NODE_H
