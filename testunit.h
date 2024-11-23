//
// Created by pierr on 06/11/2024.
//

#ifndef MARC_PRJ_TESTUNIT_H
#define MARC_PRJ_TESTUNIT_H

#include <stdbool.h>
#include "map.h"
#include "moves.h"

/**
 * @brief Execute all units tests
 */
void unitTest();

/**
 * @brief Unit to test Tree with manual construction.
 * @param displayTree Display tree or not
 */
void nodeTest(bool displayTree);

/**
 * @brief Unit to test Tree with automated construction.
 * @param map The map to test building
 * @param displayTree Display tree or not
 */
void treeAutoConstructionTest(t_map map, bool displayTree);

/**
 * @brief Unit to test Tree with automated construction.
 * @param map The map to test building
 * @param displayTree Display tree or not
 * @param lenMvtArr The len of @param mvtArr
 * @param mvtArr The available move to execute
 * @param locInit The initial localisation
 */
void treeAutoConstructionPreDefinedMvtSetTest(t_map map, bool displayTree, int lenMvtArr, t_move *mvtArr,
                                              t_localisation locInit);

/**
 * Show previous informations about the map
 * @param map the map to retrieve information from
 */
void displayMapInfos(t_map map);

#endif //MARC_PRJ_TESTUNIT_H
