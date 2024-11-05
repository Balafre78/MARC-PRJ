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
        ptr->sons = malloc(nbSons * sizeof(t_node **));
        if (ptr->sons == NULL) {
            fprintf(stderr, "Cannot allocate mem!\n");
            exit(EXIT_FAILURE);
        }
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

    int *usedMoveArr = calloc(lenArr, sizeof(int));
    if (usedMoveArr == NULL) {
        fprintf(stderr, "Cannot allocate mem!\n");
        exit(EXIT_FAILURE);
    }

    tree->root = createNode(COST_UNDEF, -1, lenArr);
    for (int i = 0; i < lenArr; i++) {
        tree->root->sons[i] = buildTreeRec(map, tree, usedMoveArr, i, 0, iniLoc);
    }

    return tree;
}

t_node *buildTreeRec(t_map map, t_tree *tree, int *usedMoveArr, int idxUMA, int depth, t_localisation prevLoc) {
    t_node *ptr;
    usedMoveArr[idxUMA] = 1;

#ifdef DEBUG
    printf("usedMoveArr[idxUMA]: ");
    for (int i = 0; i < tree->lenArr; i++) {
        printf("%d", usedMoveArr[i]);
    }
    printf("\n");
#endif


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
        localCost = map.costs[newloc.pos.y][newloc.pos.x];
        if (localCost >= COST_DIE ) {
            nodeNbSons = 0;
            localCost = COST_DIE ;
        } else if (tree->maxDepth <= depth) {
            nodeNbSons = 0;
        } else {
            //nodeNbSons = tree->maxDepth +1 - depth;
            nodeNbSons = tree->lenArr - depth - 1;
        }
    }

    ptr = createNode(localCost, depth, nodeNbSons);

    if (nodeNbSons > 0) {
        //printf("Enter SON\n");
        int d = 0;
        for (int i = 0; i < tree->lenArr; i++) {
            if (usedMoveArr[i] == 0) {
                ptr->sons[i-d] = buildTreeRec(map, tree, usedMoveArr, i, depth + 1, newloc);
            } else {
                d++;
            }
        }
        //printf("END SON\n");


    }


    usedMoveArr[idxUMA] = 0;
    return ptr;
}
