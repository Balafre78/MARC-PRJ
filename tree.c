//
// Created by pierr on 23/10/2024.
//

#include "tree.h"

/**
 * @brief Build recursivly the tree
 * @param map Map to analyse
 * @param tree Used for his properties
 * @param usedMoveArr Arr to store used mvt 1 if used 0 else
 * @param idxUMA the index in the @param usedMoveArr to known which move will choose the robot for its next move
 * @param depth the depth of the partial tree root
 * @param prevLoc the previous location of the robot
 * @return Pointer to the completed node
 */
t_node *buildTreeRec(t_map map, t_tree *tree, int *usedMoveArr, int idxUMA, int depth, t_localisation prevLoc);

t_node *createNode(int value, int depth, int nbSons) {
    t_node *ptr = malloc(sizeof(t_node));
    if (ptr == NULL) {
        fprintf(stderr, "Cannot allocate mem!\n");
        exit(EXIT_FAILURE);
    }

    ptr->value = value;
    ptr->depth = depth;
    ptr->nbSons = nbSons;

    if (nbSons > 0) {
        ptr->sons = malloc(nbSons * sizeof(t_node **));
        if (ptr->sons == NULL) {
            fprintf(stderr, "Cannot allocate mem!\n");
            exit(EXIT_FAILURE);
        }
        // OPT-IN
        // Assign node sons to NULL to let (manual) error throw (if they detect no affectation)
        for (int i = 0; i < nbSons; i++) {
            ptr->sons[i] = NULL;
        }
    } else {
        ptr->sons = NULL;
    }
    return ptr;
}

void deleteNode(t_node *node) {
    if (node->nbSons > 0) {
        // Delete recursively all sons
        for (int i = 0; i < node->nbSons; i++)
            if (node->sons[i] != NULL)
                deleteNode(node->sons[i]);

        free(node->sons);
        node->sons = NULL;
    }
    free(node);
}

t_tree *buildTree(t_map map, int maxDepth, int lenArr, t_move *moveArr, t_localisation iniLoc) {
    t_tree *tree = malloc(sizeof(t_tree));
    if (tree == NULL) {
        fprintf(stderr, "Cannot allocate mem!\n");
        exit(EXIT_FAILURE);
    }

    tree->lenArr = lenArr;
    tree->moveArr = moveArr;
    tree->maxDepth = maxDepth;

    // int *usedMoveArr is an array to store if the move have been used 0 if unused 1 else
    int *usedMoveArr = calloc(lenArr, sizeof(int));
    if (usedMoveArr == NULL) {
        fprintf(stderr, "Cannot allocate mem!\n");
        exit(EXIT_FAILURE);
    }

    // The value of the first node should be undefined and it's not important ; depth is -1
    tree->root = createNode(COST_UNDEF, -1, lenArr);
    for (int i = 0; i < lenArr; i++) {
        // Force to generate each possible sons
        tree->root->sons[i] = buildTreeRec(map, tree, usedMoveArr, i, 0, iniLoc);
    }

    return tree;
}

t_node *buildTreeRec(t_map map, t_tree *tree, int *usedMoveArr, int idxUMA, int depth, t_localisation prevLoc) {
    t_node *ptr;

    // LOCK THE MOVE
    usedMoveArr[idxUMA] = 1;

#ifdef DEBUG
    printf("usedMoveArr[idxUMA]: ");
    for (int i = 0; i < tree->lenArr; i++) {
        printf("%d", usedMoveArr[i]);
    }
    printf("\n");
#endif


    // Try to make the move
    t_localisation newloc;
    if (map.soils[prevLoc.pos.y][prevLoc.pos.x] == ERG) {
        printf("Use Reg\n");
        newloc = ergMove(prevLoc, tree->moveArr[idxUMA]);
        printf("End Reg\n");
    } else {
        newloc = move(prevLoc, tree->moveArr[idxUMA]);
    }


    int localCost, nodeNbSons;

    // if the move is out the map
    if (
            newloc.pos.x < 0 ||
            newloc.pos.y < 0 ||
            newloc.pos.x >= map.x_max ||
            newloc.pos.y >= map.y_max
            ) {
        localCost = COST_DIE;
        nodeNbSons = 0;
    } else {
        localCost = map.costs[newloc.pos.y][newloc.pos.x];
        // If the move is too much expensive
        if (localCost >= COST_DIE) {
            nodeNbSons = 0;
            localCost = COST_DIE;

            // If the move is allowed by the maxdepth of the tree
        } else if (tree->maxDepth <= depth) {
            nodeNbSons = 0;
        } else {
            // Reduce to one the possibility by the actual depth (how many move where used)
            // and one more since one move is lock down
            nodeNbSons = tree->lenArr - depth - 1;
        }
    }

    ptr = createNode(localCost, depth, nodeNbSons);

    if (nodeNbSons > 0) {
        int d = 0; // the shift

        // Force to generate each possible sons
        for (int i = 0; i < tree->lenArr; i++) {

            // Does the move is already used ?
            if (usedMoveArr[i] == 0) {
                ptr->sons[i - d] = buildTreeRec(map, tree, usedMoveArr, i, depth + 1, newloc);
            } else {
                // Cannot create this son since the move is lock down
                // so the shift increments
                d++;
            }
        }
    }

    // UNLOCK THE MOVE
    usedMoveArr[idxUMA] = 0;
    return ptr;
}
