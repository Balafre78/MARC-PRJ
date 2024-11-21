#include <stdio.h>
#include "map.h"
#include "utils.h"
#include "testunit.h"
#include "map.h"

#define MAX_DEPTH 5
#define LEN_MOVE 9


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

    // Test units

    // Base information for the map
    //displayMapInfos(map);

    // Fake tree test
    //nodeTest(true);

    // Map tree building test
    //treeAutoConstructionTest(map, false);

    // Same as above but use predefined paramters
    /*
    int lenMvtArr = 4;
    t_move *mvtArr = malloc(lenMvtArr*sizeof(t_move));
    mvtArr[0] = F_10;
    mvtArr[1] = T_RIGHT;
    mvtArr[2] = T_LEFT;
    mvtArr[3] = F_10;
    t_localisation loc = {3,3, NORTH};
    treeAutoConstructionPreDefinedMvtSetTest(map, true, lenMvtArr, mvtArr, loc);
     */

    // Main process of finding the base
    mainProc(MAX_DEPTH, LEN_MOVE, false, false, true, true);


    return 0;
}
