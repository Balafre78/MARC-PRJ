//
// Created by pierr on 06/11/2024.
//

#include "testunit.h"

void nodeTest() {
    t_node *root = createNode(COST_UNDEF, -1, 3);

    t_node *left = createNode(0, 0, 2);
    t_node *mid = createNode(1, 0, 2);
    t_node *right = createNode(2, 0, 2);

    root->sons[0] = left;
    root->sons[1] = mid;
    root->sons[2] = right;

    root->sons[0]->sons[0] = createNode(1, 1, 1);
    root->sons[0]->sons[1] = createNode(2, 1, 1);

    root->sons[1]->sons[0] = createNode(0, 1, 1);
    root->sons[1]->sons[1] = createNode(2, 1, 1);

    root->sons[2]->sons[0] = createNode(0, 1, 1);
    root->sons[2]->sons[1] = createNode(1, 1, 1);

    root->sons[0]->sons[0]->sons[0] = createNode(2, 2, 0);

    root->sons[0]->sons[1]->sons[0] = createNode(1, 2, 0);

    root->sons[1]->sons[0]->sons[0] = createNode(2, 2, 0);

    root->sons[1]->sons[1]->sons[0] = createNode(0, 2, 0);

    root->sons[2]->sons[0]->sons[0] = createNode(1, 2, 0);

    root->sons[2]->sons[1]->sons[0] = createNode(0, 2, 0);

    t_tree faketree = {root, 3, NULL, 2};
    printTree(&faketree);


    deleteNode(root->sons[2]);
}

void treeAutoConstructionTest(t_map map) {
    t_move *availMoves = selMoves(9);
    t_localisation initLoc = loc_init(4,5, NORTH);

    // Let's build a 4 depth tree with 9 movements available
    t_tree *bulk = buildTree(map, 4, 9, availMoves, initLoc);

    printf("\nEND OF BUILD\n\n");

    printTree(bulk);
}