#include <stdio.h>
#include "map.h"
#include "utils.h"
#include "testunit.h"

#define MAX_DEPTH 5
#define LEN_MOVE 9

void run()
{
    //TODO
    t_map map;
    map = createMapFromFile("..\\maps\\example1.map");
    displayMap(map);

    t_localisation init_position;
    //init_position = giveStartLocation();
    init_position = loc_init(0, 0, NORTH);

    t_move* moves = selMoves(9);
    t_tree* tree;
    tree = buildTree(map, MAX_DEPTH, LEN_MOVE, moves, init_position);
    //printTree(tree);

    // Finding path
    t_node* minimal_node = minimalNode(*tree);
    t_stack path = findNodePath(minimal_node, *tree);
    displayStack(path);

    int count = 0;
    while(path.size > 0)
    {

        if(&tree->root->sons[count] == path.values)
        {

            pop(&path);
            int count = 0;
        }
        else
            count++;
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
    displayMap(map);


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