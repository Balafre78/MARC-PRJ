#include <stdio.h>
#include "map.h"
#include "tree.h"
#include "utils.h"

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

int main() {
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
    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
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


    nodeTest();

    t_move *availMoves = selMoves(9);
    t_localisation initLoc = loc_init(0,0, NORTH);
    t_tree *bulk = buildTree(map, 4, 9, availMoves, initLoc);
    printf("END OF BUILD\n");

    printTree(bulk);


    return 0;
}