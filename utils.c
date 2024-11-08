//
// Created by pierr on 23/10/2024.
//

#include "utils.h"

void printTreeRec(t_node *node, int sonsPass, int nbParentSons, int *architecture) {
#ifdef DEBUG
    printf("depth:%d\n", node->depth + 1);
    printf("nbParentSons:%d\n", nbParentSons);
    printf("sonsPass:%d\n", sonsPass);
#endif
    // Check the different stage of the tree at each depth (represented by the architecture var)
    // if there's a directory it should be  "|   "
    // if there's a nothing it should be    "    "
    // Else it means architecture is not well initialized (the node depth is incoherent) !
    for (int i = 0; i < node->depth + 1; i++) {
        if (architecture[i] == 0) {
            printf("    ");
        } else if (architecture[i] == 1) {
            printf("|   ");
        } else {
            printf("\n");
            fprintf(stderr, "Unknown arch ...!\n");
            exit(EXIT_FAILURE);
        }

    }

    // If in the end this node is the last son of the n-aire tree the print should be different
    // Modify architecture in consequence
    if (sonsPass + 1 == nbParentSons) {
        printf("`-- %d ", node->value);
        architecture[node->depth + 1] = 0;
    } else {
        printf("|-- %d ", node->value);
        architecture[node->depth + 1] = 1;
    }
    printf("\n");


    // Make recursive call for each son
    for (int i = 0; i < node->nbSons; i++) {
        if (node->sons[i] == NULL) {
            fprintf(stderr, "Incohrent node->nbSons{%d}//content!\n", node->nbSons);
            exit(EXIT_FAILURE);
        }
        printTreeRec(node->sons[i], i, node->nbSons, architecture);
    }
}

void printTree(t_tree *tree) {
    printf("Tree\n");

    // int *architecture is a var to store at each time if there's still a son to go for the same node.
    int *architecture = calloc((tree->maxDepth + 1), sizeof(int));
    if (architecture == NULL) {
        fprintf(stderr, "Cannot allocate mem!\n");
        exit(EXIT_FAILURE);
    }

    printf("`-- %d\n", tree->root->value);
    architecture[0] = 0;

    // Make recursive call for each son of the root
    for (int i = 0; i < tree->root->nbSons; i++) {
        printTreeRec(tree->root->sons[i], i, tree->root->nbSons, architecture);
    }


    free(architecture);
}

t_move *selMoves(int size) {
    int movePool[AMOUNT_MVT] = ARR_MOVEPOOL;

    int choice, acc, sum;
    sum = BASE_SUM;

    t_move *moveArr = malloc(size * sizeof(t_move));

    // Try to choose one mvt accros all 100 moves (so each move height is different)
    for (int i = 0; i < size; i++) {
        choice = rand() % sum;

        // Try to find which move have been chosen and retire form the good stack.
        acc = 0;
        for (int idxMvt = 0; idxMvt < AMOUNT_MVT; idxMvt++) {
            //printf("selMvt:%d | acc:%2d | choice:%2d | acc + movePool[idxMvt]:%2d\n", idxMvt, acc, choice, acc + movePool[idxMvt]);
            if (acc <= choice && choice < acc + movePool[idxMvt]) {
                movePool[idxMvt]--;
                moveArr[i] = (t_move) idxMvt;
                break;
            }
            acc += movePool[idxMvt];
        }
        sum--;
    }

#ifdef DEBUG
    for (int i = 0; i < size; i++) {
        printf("Move %d: %d\n", i, moveArr[i]);
    }
#endif
    return moveArr;
}

void delMoves(t_move *moveArr) {
    free(moveArr);
}

t_localisation ergMove(t_localisation loc, t_move mvt) {
    t_move *ptr = &mvt;
    switch (mvt) {
        case F_10:
        case B_10:
        case T_LEFT:
        case T_RIGHT:
            ptr = NULL;
            break;
        case F_20:
            *ptr = F_10;
            break;
        case F_30:
            *ptr = F_20;
            break;
        case U_TURN:
            if (rand() % 2 == 1)
                *ptr = T_RIGHT;
            else
                *ptr = T_LEFT;
            break;
    }

    if (ptr != NULL)
        loc = move(loc, *ptr);

    return loc;

}