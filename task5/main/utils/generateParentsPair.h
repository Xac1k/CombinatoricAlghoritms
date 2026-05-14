//
// Created by xac1k on 4/14/26.
//

#ifndef TASK5_SELECTIONPARENTS_H
#define TASK5_SELECTIONPARENTS_H
#include <stdexcept>

#include "types.h"

inline ParentsPairVect GenerateParentsPair(const Population& population, size_t countOfParents) {
    ParentsPairVect res;
    if (population.size() == 1) return res;
    const auto maxIdx = population.size() - 1;
    for (int i = 0; i < countOfParents; ++i) {
        const size_t firstParentIdx = Random::getInt(0, maxIdx);
        size_t secondParentIdx = Random::getInt(0, maxIdx);

        while (firstParentIdx == secondParentIdx) { secondParentIdx = Random::getInt(0, maxIdx); }
        res.emplace_back(firstParentIdx, secondParentIdx);
    }
    return res;
}

#endif //TASK5_SELECTIONPARENTS_H