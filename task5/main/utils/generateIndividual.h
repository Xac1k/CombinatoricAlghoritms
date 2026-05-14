//
// Created by xac1k on 4/13/26.
//

#ifndef TASK5_GENERATEINDIVIDUAL_H
#define TASK5_GENERATEINDIVIDUAL_H
#include "rand.h"
#include "types.h"

inline Individual generateIndividual(const size_t size, const double rate) {
    Individual ind = {};
    ind.reserve(size);

    for (size_t i = 0; i < size; i++)
        ind.push_back(Random::getDouble() <= rate ? 1 : 0);

    return ind;
}

#endif //TASK5_GENERATEINDIVIDUAL_H
