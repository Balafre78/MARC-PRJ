#include <stdio.h>
#include "map.h"
#include "utils.h"
#include "testunit.h"
#include "map.h"

#define MAX_DEPTH 5
#define LEN_MOVE 9

void run() {
    //TODO
    t_map map;
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif
    //displayMap(map);

    t_localisation initPosition;
    t_position basePosition = getBaseStationPosition(map);
    printf("basePosition: %d %d\n", basePosition.x, basePosition.y);
    initPosition = giveStartLocation(map);

    t_tree *tree;

    while (initPosition.pos.x != basePosition.x || initPosition.pos.y != basePosition.y) {
        tree = buildTree(map, MAX_DEPTH, LEN_MOVE, selMoves(9), initPosition);

        /*
        printf("Available moves :\n");
        for (int i = 0; i < tree->lenArr; i++)
            printf("Move %d: %s\n", i + 1, getMoveAsString(tree->moveArr[i]));
        */
        //printTree(tree);

        // Finding path
        t_node *minimal_node = minimalNode(*tree);
        t_stack path = findNodePath(minimal_node, *tree);
        //displayStack(path);

        int pathLen = path.nbElts;
        t_move *mvtArr = malloc(pathLen * sizeof(t_move));
        int *structMvtArr = calloc(LEN_MOVE, sizeof(t_move));

        int passSons;
        int idxMvtArr = 0;
        t_node *nodePtr = tree->root;
        while (path.nbElts > 0) {
            // First step : find the corresponding node ; count passed son.
            // Second Step : Find out which movement was used (minus passed son)
            passSons = 0;
            for (int i = 0; i < LEN_MOVE; i++) {
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
            printf("Move %d: %s\n", i + 1, getMoveAsString(tree->moveArr[mvtArr[i]]));
            initPosition = move(initPosition, tree->moveArr[mvtArr[i]]);
            //printf("Arrived @(x:%d,y:%d) Orri:%d\n", initPosition.pos.x, initPosition.pos.y, initPosition.ori);
        }
        printf("Arrived @(x:%d,y:%d)\n", initPosition.pos.x, initPosition.pos.y);

        free(structMvtArr);
        deleteTree(tree);
        free(mvtArr);

        }
}


int main() {
    // Define the seed either with predefined SEED macro or with some randomness from time
#ifdef SEED
    srand(SEED);
#else
    unsigned int seed = time(NULL);
    printf("seed:%u\n", seed);
    srand(seed);
#endif

    t_map map;

    // The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif
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
    //displayMap(map);


    // Test units
    /*
    nodeTest(true); // Fake tree test

    treeAutoConstructionTest(map, false); // Map tree building test

    int lenMvtArr = 4;
    t_move mvtArr[4] = {F_10, T_RIGHT, T_LEFT, F_10};
    t_localisation loc = {3,3, NORTH};
    treeAutoConstructionPreDefinedMvtSetTest(map, true, lenMvtArr, mvtArr, loc);

    */
    run();


    return 0;
}
