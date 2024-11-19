//
// Created by pierr on 06/11/2024.
//

#include "testunit.h"

void nodeTest(bool displayTree) {
    printf("\nFAKE TREE TEST\n");
    t_node *root = createNode(COST_UNDEF, -1, 3, NULL);

    t_node *left = createNode(0, 0, 2, NULL);
    t_node *mid = createNode(1, 0, 2, NULL);
    t_node *right = createNode(2, 0, 2, NULL);

    root->sons[0] = left;
    root->sons[1] = mid;
    root->sons[2] = right;

    root->sons[0]->sons[0] = createNode(1, 1, 1, NULL);
    root->sons[0]->sons[1] = createNode(2, 1, 1, NULL);

    root->sons[1]->sons[0] = createNode(0, 1, 1, NULL);
    root->sons[1]->sons[1] = createNode(2, 1, 1, NULL);

    root->sons[2]->sons[0] = createNode(0, 1, 1, NULL);
    root->sons[2]->sons[1] = createNode(1, 1, 1, NULL);

    root->sons[0]->sons[0]->sons[0] = createNode(2, 2, 0, NULL);

    root->sons[0]->sons[1]->sons[0] = createNode(1, 2, 0, NULL);

    root->sons[1]->sons[0]->sons[0] = createNode(2, 2, 0, NULL);

    root->sons[1]->sons[1]->sons[0] = createNode(0, 2, 0, NULL);

    root->sons[2]->sons[0]->sons[0] = createNode(1, 2, 0, NULL);

    root->sons[2]->sons[1]->sons[0] = createNode(0, 2, 0, NULL);

    t_tree faketree = {root, 3, NULL, 2};
    if(displayTree) printTree(&faketree);

    t_node *minNode = minimalNode(faketree);
    printf("Minimal node address : %p\n", minNode);
    printf("Minimal node value : %d\n", minNode->value);
}

void treeAutoConstructionTest(t_map map, bool displayTree) {
    printf("\nMAP TREE BUILDING TEST\n");
    t_move *availMoves = selMoves(9);
    t_localisation initLoc = loc_init(4,5, NORTH);
    //t_localisation initLoc = loc_init(0,1, EAST);

    // Let's build a 4 depth tree with 9 movements available
    printf("Building...\n");
    t_tree *bulk = buildTree(map, 5, 9, availMoves, initLoc);
    printf("End building!\n");

    if(displayTree) printTree(bulk);

    t_node *minNode = minimalNode(*bulk);
    printf("Minimal node address : %p\n", minNode);
    printf("Minimal node value : %d\n", minNode->value);
    t_stack path = findNodePath(minNode, *bulk);
    displayStack(path);
    deleteTree(bulk);
    bulk = NULL;
}

void treeAutoConstructionPreDefinedMvtSetTest(t_map map, bool displayTree, int lenMvtArr, t_move *mvtArr, t_localisation locInit) {
    printf("\nMAP TREE BUILDING TEST\n");

    // Let's build a 4 depth tree with lenMvtArr movements available
    printf("Building...\n");
    t_tree *bulk = buildTree(map, 5, lenMvtArr, mvtArr, locInit);
    printf("End building!\n");

    if(displayTree) printTree(bulk);

    t_node *minNode = minimalNode(*bulk);
    printf("Minimal node address : %p\n", minNode);
    printf("Minimal node value : %d\n", minNode->value);
    t_stack path = findNodePath(minNode, *bulk);
    displayStack(path);
    deleteTree(bulk);
    bulk = NULL;
}