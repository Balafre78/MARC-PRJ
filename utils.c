//
// Created by pierr on 23/10/2024.
//

#include "utils.h"

void printTreeRec(t_node *node, int sonsPass, int nbParentSons, int *architecture) {
    //printf("depth:%d\n", node->depth + 2);
    //printf("nbSons:%d\n", nbParentSons);
    //printf("sonsPass:%d\n", sonsPass);
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
    if (sonsPass + 1 == nbParentSons) {
        printf("`-- %d\n", node->value);
        architecture[node->depth + 1] = 0;
    } else {
        printf("|-- %d\n", node->value);
        architecture[node->depth + 1] = 1;
    }
    for (int i = 0; i < node->nbSons; i++) {
        printTreeRec(node->sons[i], i, node->nbSons, architecture);
    }
}

void printTree(t_tree *tree) {
    printf("Tree\n");
    int *architecture = calloc((tree->maxDepth + 1), sizeof(int));
    if (architecture == NULL) {
        fprintf(stderr, "Cannot allocate mem!\n");
        exit(EXIT_FAILURE);
    }

    printf("`-- %d\n", tree->root->value);
    architecture[0] = 0;

    for (int i = 0; i < tree->root->nbSons; i++) {
        printTreeRec(tree->root->sons[i], i, tree->root->nbSons, architecture);
    }


    free(architecture);
}

t_move *selMoves(int size) {
    int movePool[AMOUNT_MVT] = ARR_MOVEPOOL;

#ifdef SEED
    srand(SEED);
#else
    srand(time(NULL));
#endif

    int choice, acc, sum;
    sum = BASE_SUM;

    t_move *moveArr = malloc(size * sizeof(t_move));

    for (int i = 0; i < size; i++) {
        choice = rand() % sum;

        acc = 0;
        for (int j = 0; j < 7; j++) {
            if (acc <= choice && choice < acc + movePool[j]) {
                movePool[j]--;
                moveArr[i] = (t_move) j;
            }
            acc += movePool[j];
        }
        sum--;
    }

    return moveArr;
}