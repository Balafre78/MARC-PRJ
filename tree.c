//
// Created by pierr on 23/10/2024.
//

#include "tree.h"

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
        ptr->sons = malloc(nbSons * sizeof(int));
        if (ptr->sons == NULL) {
            fprintf(stderr, "Cannot allocate mem!\n");
            exit(EXIT_FAILURE);
        }
    } else {
        ptr->sons = NULL;
    }
    return ptr;
}

void deleteNode(t_node *node) {
    if (node->nbSons > 0) {
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

    int *usedMoveArr = calloc(lenArr, sizeof(int));
    if (usedMoveArr == NULL) {
        fprintf(stderr, "Cannot allocate mem!\n");
        exit(EXIT_FAILURE);
    }

    tree->root = createNode(COST_UNDEF, -1, lenArr);
    for (int i = 0; i < lenArr; i++) {
        tree->root->sons[i] = buildTreeRec(map, tree, usedMoveArr, 0, iniLoc);
    }

    return tree;
}

t_node *buildTreeRec(t_map map, t_tree *tree, int *usedMoveArr, int depth, t_localisation prevLoc) {
#ifdef DEBUG
    printf("usedMoveArr[idxUMA]: ");
    for (int i = 0; i < tree->lenArr; i++) {
        printf("%d", usedMoveArr[i]);
    }
    printf("\n");
#endif
    t_node *ptr;
    int idxUMA = 0;

    // We are supposed that MoveArr is large enough for our purpose
    while (idxUMA < tree->lenArr) {
        if (usedMoveArr[idxUMA] != 1)
            break;
        idxUMA++;
    }
    if (idxUMA >= tree->lenArr) {
        fprintf(stderr, "idxUMA is above tree->lenArr!\n");
        exit(EXIT_FAILURE);
    }
    usedMoveArr[idxUMA] = 1;

    t_localisation newloc = move(prevLoc, tree->moveArr[idxUMA]);

    int localCost, nodeNbSons;
    if (
            newloc.pos.x < 0 ||
            newloc.pos.y < 0 ||
            newloc.pos.x >= map.x_max ||
            newloc.pos.y >= map.y_max
            ) {
        localCost = COST_DIE;
        nodeNbSons = 0;
    } else {
        localCost = map.costs[newloc.pos.x][newloc.pos.y];
        if (localCost >= COST_DIE) {
            nodeNbSons = 0;
        } else {
            nodeNbSons = tree->maxDepth - depth - 1;
        }
    }

    ptr = createNode(localCost, depth, nodeNbSons);

    //printf("nodeNbSons:%d\n", nodeNbSons);
    for (int i = 0; i < nodeNbSons; i++) {
        ptr->sons[i] = buildTreeRec(map, tree, usedMoveArr, depth + 1, newloc);
    }


    usedMoveArr[idxUMA] = 0;
    return ptr;
}