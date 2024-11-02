#include <stdio.h>
#include "map.h"
#include "tree.h"
#include "utils.h"

void nodeTest() {
    t_node *root = createNode(COST_UNDEF, 0, 3);

    t_node *left = createNode(0, 1, 2);
    t_node *mid = createNode(1, 1, 2);
    t_node *right = createNode(2, 1, 2);

    root->sons[0] = left;
    root->sons[1] = mid;
    root->sons[2] = right;

    root->sons[0]->sons[0] = createNode(1, 2, 1);
    root->sons[0]->sons[1] = createNode(2, 2, 1);

    root->sons[1]->sons[0] = createNode(0, 2, 1);
    root->sons[1]->sons[1] = createNode(2, 2, 1);

    root->sons[2]->sons[0] = createNode(0, 2, 1);
    root->sons[2]->sons[1] = createNode(1, 2, 1);

    root->sons[0]->sons[0]->sons[0] = createNode(2, 3, 0);

    root->sons[0]->sons[1]->sons[0] = createNode(1, 3, 0);

    root->sons[1]->sons[0]->sons[0] = createNode(2, 3, 0);

    root->sons[1]->sons[1]->sons[0] = createNode(0, 3, 0);

    root->sons[2]->sons[0]->sons[0] = createNode(1, 3, 0);

    root->sons[2]->sons[1]->sons[0] = createNode(0, 3, 0);

    t_tree faketree = {root, 3, NULL, 3};
    printTree(&faketree);


    deleteNode(root->sons[2]);
}

int main() {
    /*t_map map;

    // The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif
    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);
    return 0;*/
    nodeTest();

    return 0;
}