//
// Created by Raphy on 12/11/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "node.h"

t_node *createNode(int value, int depth, int nbSons, t_node *parent) {
    t_node *ptr = malloc(sizeof(t_node));
    if (ptr == NULL) {
        fprintf(stderr, "Cannot allocate mem!\n");
        exit(EXIT_FAILURE);
    }

    ptr->value = value;
    ptr->depth = depth;
    ptr->nbSons = nbSons;
    ptr->parent = parent;

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