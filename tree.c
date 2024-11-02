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