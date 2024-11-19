//
// Created by pierr on 06/11/2024.
//

#ifndef MARC_PRJ_TESTUNIT_H
#define MARC_PRJ_TESTUNIT_H

#include "map.h"
#include "tree.h"
#include "utils.h"


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
void treeAutoConstructionPreDefinedMvtSetTest(t_map map, bool displayTree, int lenMvtArr, t_move *mvtArr, t_localisation locInit);

#endif //MARC_PRJ_TESTUNIT_H
