//
// Created by pierr on 23/10/2024.
//

#include "tree.h"

/**
 * @brief Build recursively the tree
 * @param map Map to analyse
 * @param tree Used for his properties
 * @param usedMoveArr Arr to store used mvt 1 if used 0 else
 * @param idxUMA the index in the @param usedMoveArr to known which move will choose the robot for its next move
 * @param depth the depth of the partial tree root
 * @param prevLoc the previous location of the robot
 * @return Pointer to the completed node
 */
t_node *buildTreeRec(t_map map, t_tree *tree, bool *usedMoveArr, int idxUMA, int depth, t_localisation prevLoc);

/**
 * @brief Search recursively the minimal node
 * @param node Node to compare
 * @param currentMin Node to compare with
 * @return The minimal node
 */
t_node *minimalNodeRec(t_node *node, t_node *currentMin);

/**
 * @brief Destroy a node and all his children in the heap
 * @param node The node to delete
 */
void deleteNodeRec(t_node *node);

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

void deleteNodeRec(t_node *node) {
    if (node->nbSons > 0) {
        // Delete recursively all sons
        for (int i = 0; i < node->nbSons; i++)
            if (node->sons[i] != NULL)
                deleteNodeRec(node->sons[i]);

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
    bool *usedMoveArr = calloc(lenArr, sizeof(bool));
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

t_node *buildTreeRec(t_map map, t_tree *tree, bool *usedMoveArr, int idxUMA, int depth, t_localisation prevLoc) {
    t_node *ptr;

    // LOCK THE MOVE
    usedMoveArr[idxUMA] = true;

#ifdef DEBUG
    printf("usedMoveArr[idxUMA]: ");
    for (int i = 0; i < tree->lenArr; i++) {
        printf("%d", usedMoveArr[i]);
    }
    printf("\n");
#endif


    // Try to make the move
    t_localisation newloc;
    switch (map.soils[prevLoc.pos.y][prevLoc.pos.x]) {
        case ERG:
            newloc = ergMove(prevLoc, tree->moveArr[idxUMA]);
            break;
        default:
            newloc = move(prevLoc, tree->moveArr[idxUMA]);
            break;
    }


    // Reduce to one the possibility by the actual depth (how many move where used)
    // and one more since one move is lock down
    int localCost, nodeNbSons = tree->lenArr - depth - 1;

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

        // modification based on soil is more reliable than costs
        switch (map.soils[newloc.pos.y][newloc.pos.x]) {
            case BASE_STATION:
                nodeNbSons = 0;
                localCost = 0;
                break;
            case CREVASSE:
                nodeNbSons = 0;
                localCost = COST_DIE;
                break;
        }

        // If the move is allowed by the maxdepth of the tree
        if (tree->maxDepth <= depth) {
            nodeNbSons = 0;
        }
    }

    ptr = createNode(localCost, depth, nodeNbSons);

    if (nodeNbSons > 0) {
        int d = 0; // the shift

        // Force to generate each possible sons
        for (int i = 0; i < tree->lenArr; i++) {

            // Does the move is already used ?
            if (usedMoveArr[i] == false) {
                ptr->sons[i - d] = buildTreeRec(map, tree, usedMoveArr, i, depth + 1, newloc);
            } else {
                // Cannot create this son since the move is lock down
                // so the shift increments
                d++;
            }
        }
    }

    // UNLOCK THE MOVE
    usedMoveArr[idxUMA] = false;
    return ptr;
}

void deleteTree(t_tree *tree)
{
    deleteNodeRec(tree->root);
    delMoves(tree->moveArr);
    free(tree);
}

t_node *minimalNodeRec(t_node *node, t_node *currentMin)
{
    if (node == NULL) return currentMin;

    // If no currentMin node defined or finding a new minimal node
    if (currentMin == NULL || node->value < currentMin->value) {
        currentMin = node;
    }

    // No node with value under 0
    if(currentMin != NULL && currentMin->value == 0) return currentMin;

    // Browsing all the sons of the current node
    for (int i = 0; i < node->nbSons; i++) {
        currentMin = minimalNodeRec(node->sons[i], currentMin);
    }

    return currentMin;
}

t_node *minimalNode(t_tree tree)
{
    if(tree.root == NULL) return NULL;
    return minimalNodeRec(tree.root, NULL);
}

t_stack findNodePath(t_node *node, t_tree tree)
{
    t_stack path = createStack(tree.maxDepth);
    //TODO t_stack is not adapted to store t_node pointers! Modifying given code ?
    return path;
}