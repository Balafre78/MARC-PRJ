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
    t_tree *tree = malloc(sizeof(tree));
    if (tree == NULL) {
        fprintf(stderr, "Cannot allocate mem!\n");
        exit(EXIT_FAILURE);
    }

    tree->lenArr = lenArr;
    tree->moveArr = moveArr;
    tree->maxDepth = maxDepth;

    int *usedMoveArr = malloc(lenArr * sizeof(int));
    tree->root = createNode(COST_UNDEF, -1, lenArr);
    for (int i = 0; i < lenArr; i++) {
        tree->root->sons[i] = buildTreeRec(map, tree, usedMoveArr, 0, iniLoc);
    }

    return tree;
}

t_node *buildTreeRec(t_map map, t_tree *tree, int *usedMoveArr, int depth, t_localisation prevLoc) {
    int idxUMA = 0;

    // We are supposed that MoveArr is large enough for our purpose
    while (idxUMA < tree->lenArr) {
        if (usedMoveArr[idxUMA] != 0)
            break;
        idxUMA++;
    }
    usedMoveArr[idxUMA] = 1;

    t_localisation newloc = move(prevLoc, tree->moveArr[idxUMA]);

    t_node *ptr = createNode(map.costs[newloc.pos.x][newloc.pos.y], depth, tree->maxDepth - depth);

    for (int i = 0; i < tree->maxDepth - depth; i++) {
        ptr->sons[i] = buildTreeRec(map, tree, usedMoveArr, depth + 1, newloc);
    }


    usedMoveArr[idxUMA] = 0;
    return ptr;
}