//
// Created by pierr on 23/10/2024.
//

#include "utils.h"

void printTreeRec(t_node *node, int sonsPass, int *architecture) {
    for (int i = 0; i < node->depth + 1; i++) {
        switch (architecture[i]) {
            case 0:
                printf("    ");
                break;
            case 1:
                printf("|   ");
                break;
        }

    }
    if (sonsPass == node->nbSons) {
        printf("`-- %d\n", node->value);
        architecture[node->depth + 1] = 0;
    } else {
        printf("|-- %d\n", node->value);
        architecture[node->depth + 1] = 1;
    }
    for (int i = 0; i < node->nbSons; i++) {
        printTreeRec(node->sons[i], i, architecture);
    }
}

void printTree(t_tree *tree) {
    printf("Tree\n");
    int *architecture = calloc((tree->maxDepth + 1), sizeof(int));
    if (architecture == NULL) {
        fprintf(stderr, "Cannot allocate mem!\n");
        exit(EXIT_FAILURE);
    }
    printTreeRec(tree->root, tree->root->nbSons, architecture);
    free(architecture);
}