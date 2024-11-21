//
// Created by pierr on 06/11/2024.
//

#include "testunit.h"
#include "utils.h"

void displayMapInfos(t_map map) {
    printf("Map created with dimensions (y:%d) x (x:%d)\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);
}

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
    if (displayTree) printTree(&faketree);

    t_node *minNode = minimalNode(faketree);
    printf("Minimal node address : %p\n", minNode);
    printf("Minimal node value : %d\n", minNode->value);
}

void treeAutoConstructionTest(t_map map, bool displayTree) {
    printf("\nMAP TREE BUILDING TEST\n");
    t_move *availMoves = selMoves(9);
    t_localisation initLoc = loc_init(4, 5, NORTH);
    //t_localisation initLoc = loc_init(0,1, EAST);

    // Let's build a 4 depth tree with 9 movements available
    printf("Building...\n");
    t_tree *bulk = buildTree(map, 5, 9, availMoves, initLoc);
    printf("End building!\n");

    if (displayTree) printTree(bulk);

    t_node *minNode = minimalNode(*bulk);
    printf("Minimal node address : %p\n", minNode);
    printf("Minimal node value : %d\n", minNode->value);
    t_stack path = findNodePath(minNode, *bulk);
    displayStack(path);
    deleteTree(bulk);
    bulk = NULL;
}

void treeAutoConstructionPreDefinedMvtSetTest(t_map map, bool displayTree, int lenMvtArr, t_move *mvtArr,
                                              t_localisation locInit) {
    printf("\nMAP TREE BUILDING TEST\n");

    // Let's build a 4 depth tree with lenMvtArr movements available
    printf("Building...\n");
    t_tree *bulk = buildTree(map, 5, lenMvtArr, mvtArr, locInit);
    printf("End building!\n");

    if (displayTree) printTree(bulk);

    t_node *minNode = minimalNode(*bulk);
    printf("Minimal node address : %p\n", minNode);
    printf("Minimal node value : %d\n", minNode->value);
    t_stack path = findNodePath(minNode, *bulk);
    displayStack(path);
    deleteTree(bulk);
    bulk = NULL;
}

void mainProc(int maxDepth, int lenMove, bool displayTree, bool displayAvailMoves, bool displayTrace,
              bool displayInterSteps) {
    t_map map;
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif
    //displayMap(map);

    t_localisation initPosition;
    t_position basePosition = getBaseStationPosition(map);
    printf("Objective is @(x:%d, y:%d)\n", basePosition.x, basePosition.y);
    initPosition = giveStartLocation(map);

    t_tree *tree;

    int steps = 0;
    while (initPosition.pos.x != basePosition.x || initPosition.pos.y != basePosition.y) {
        tree = buildTree(map, maxDepth, lenMove, selMoves(lenMove), initPosition);

        if (displayAvailMoves) {
            printf("Available moves :\n");
            for (int i = 0; i < tree->lenArr; i++)
                printf("Move %d: %s\n", i + 1, getMoveAsString(tree->moveArr[i]));
        }

        if (displayTree)
            printTree(tree);

        // Finding path
        t_node *minimal_node = minimalNode(*tree);
        t_stack path = findNodePath(minimal_node, *tree);
        //displayStack(path);

        int pathLen = path.nbElts;
        t_move *mvtArr = malloc(pathLen * sizeof(t_move));
        int *structMvtArr = calloc(lenMove, sizeof(t_move));

        int passSons;
        int idxMvtArr = 0;
        t_node *nodePtr = tree->root;
        while (path.nbElts > 0) {
            // First step : find the corresponding node ; count passed son.
            // Second Step : Find out which movement was used (minus passed son)
            passSons = 0;
            for (int i = 0; i < lenMove; i++) {
                if (structMvtArr[i] == 1) {
                    passSons++;
                    continue;
                }
                if (nodePtr->sons[i - passSons] == top(path)) {
                    mvtArr[idxMvtArr] = i;
                    structMvtArr[i] = 1;
                    nodePtr = pop(&path);
                    break;
                }
            }

            idxMvtArr++;
        }
        for (int i = 0; i < pathLen; i++) {
            //printf("Move %d: %i\n", i + 1, mvtArr[i] + 1);
            if (displayTrace)
                printf("Move %d: %s\n", i + 1, getMoveAsString(tree->moveArr[mvtArr[i]]));
            initPosition = move(initPosition, tree->moveArr[mvtArr[i]]);
            //printf("Arrived @(x:%d,y:%d) Orri:%d\n", initPosition.pos.x, initPosition.pos.y, initPosition.ori);
        }
        if (displayInterSteps)
            printf("Arrived @(x:%d,y:%d)\n", initPosition.pos.x, initPosition.pos.y);

        free(structMvtArr);
        deleteTree(tree);
        free(mvtArr);

        steps++;
    }
    printf("Arrived at the base station in %d steps !\n", steps);
}
