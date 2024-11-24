#include <stdio.h>
#include "map.h"
#include "utils.h"
#include "testunit.h"
#include "complexity/timer.h"

// Uncomment SEED macro to use fixed seed for random generation
#define SEED 1732121615

#define MAX_DEPTH 5
#define LEN_MOVE 9

/**
 * @brief The main process to route the rover to it's base station
 * @param maxDepth the max of movements to choose
 * @param lenMove the amount of available movements
 * @param displayTree display the tree
 * @param displayAvailMoves display the phase available moves
 * @param displaySelectedMoves display the phase selected moves
 * @param displayPhaseResult display the phase rover end position
 * @param displayTimers display timers
 */
void runRover(int maxDepth, int lenMove, bool displayTree, bool displayAvailMoves, bool displaySelectedMoves,
              bool displayPhaseResult, bool displayTimers);

/**
 * @brief Define the seed either with fixed SEED macro or with randomness
 */
void defineSeed();


int main()
{
    // Defining the seed
    defineSeed();
    // Unit test
    // unitTest();
    // Main process of finding the base
    runRover(MAX_DEPTH, LEN_MOVE, false, true, true, true, true);
    return 0;
}

void runRover(int maxDepth, int lenMove, bool displayTree, bool displayAvailMoves, bool displaySelectedMoves,
              bool displayPhaseResult, bool displayTimers) {
    t_map map;
    #if defined(_WIN32) || defined(_WIN64)
        map = createMapFromFile("..\\maps\\example1.map");
    #else
        map = createMapFromFile("../maps/example1.map");
    #endif
    //displayMap(map);

    t_timer runTimer, buildTreeTimer, minimalNodeTimer, findNodePathTimer = createTimer();
    startTimer(&runTimer);

    t_localisation roverPosition = map.startLocalisation;;
    t_position basePosition = getBaseStationPosition(map);
    printf("-> Base at position (x:%d, y:%d)\n", basePosition.x, basePosition.y);
    printf("-> Starting at (x:%d, y:%d)\n", roverPosition.pos.x, roverPosition.pos.y);

    t_tree *tree;
    bool finishOnReg = false;

    int phase = 0;
    while (roverPosition.pos.x != basePosition.x || roverPosition.pos.y != basePosition.y) {
        // START OF PHASE
        phase++;
        if(finishOnReg) {
            printf("-> PHASE %d (Damaged)\n", phase);
        } else {
            printf("-> PHASE %d\n", phase);
        }
        enum e_move* mvt = selMoves(lenMove);

        // TREE BUILDING
        startTimer(&buildTreeTimer);
        if(finishOnReg) {
            tree = buildTree(map, maxDepth-1, lenMove, mvt, roverPosition);
            finishOnReg = false;
        } else {
            tree = buildTree(map, maxDepth, lenMove, mvt, roverPosition);
        }
        stopTimer(&buildTreeTimer);

        // AVAILABLE MOVES
        if (displayAvailMoves) {
            printf("\t- Available moves: [");
            int i;
            for (i = 0; i < tree->lenArr-1; i++)
                printf("%s, ", getMoveAsString(tree->moveArr[i]));
            printf("%s] (%d)\n", getMoveAsString(tree->moveArr[i]), lenMove);
        }

        if (displayTree)
            printTree(tree);

        // FINDING MINIMAL NODE
        startTimer(&minimalNodeTimer);
        t_node *minimal_node = minimalNode(*tree);
        stopTimer(&minimalNodeTimer);

        // FINDING PATH
        startTimer(&findNodePathTimer);
        t_stack path = findNodePath(minimal_node, *tree);
        stopTimer(&findNodePathTimer);

        // EXECUTE MOVES
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
        if(displaySelectedMoves) printf("\t- Selected moves (max %d):\n", tree->maxDepth+1);
        for (int i = 0; i < pathLen; i++) {
            //printf("Move %d: %i\n", i + 1, mvtArr[i] + 1);
            roverPosition = move(roverPosition, tree->moveArr[mvtArr[i]], map);
            finishOnReg = map.soils[roverPosition.pos.x][roverPosition.pos.y] == REG || finishOnReg;
            if (displaySelectedMoves)
                printf("\t\t%d. %s\n", i + 1, getMoveAsString(tree->moveArr[mvtArr[i]]));
            //printf("Arrived @(x:%d,y:%d) Orri:%d\n", roverPosition.pos.x, roverPosition.pos.y, roverPosition.ori);
        }

        // RESULTS
        if (displayPhaseResult)
            printf("\t- At position (x:%d,y:%d)\n", roverPosition.pos.x, roverPosition.pos.y);


        free(structMvtArr);
        deleteTree(tree);
        free(mvtArr);


        // TIMERS
        if(displayTimers) {
            printf("\t- Timers:\n");
            printf("\t\tTree building: ");
            displayTimer(&buildTreeTimer);
            printf("\t\tMinimal node finding: ");
            displayTimer(&minimalNodeTimer);
            printf("\t\tPath finding: ");
            displayTimer(&findNodePathTimer);
        }
        // END OF PHASE
    }
    printf("-> Arrived at the base station in %d phase(s) !\n", phase);

    stopTimer(&runTimer);
    if(displayTimers) {
        printf("\tRun time: ");
        displayTimer(&runTimer);
    }
}

void defineSeed()
{
    #ifdef SEED
        printf("-> Seed: %u (fixed)\n", SEED);
    #else
    #include <time.h>
    #define SEED time(NULL)
        printf("-> Seed: %u (random)\n", SEED);
    #endif
        srand(SEED);
}

