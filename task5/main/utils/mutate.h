//
// Created by xac1k on 4/13/26.
//

#ifndef TASK5_MUTATE_H
#define TASK5_MUTATE_H
#include "rand.h"
#include "types.h"

inline void Mutate(Individual& individual, double rate) {
    if (Random::getBool(rate)) {
        const size_t idx = Random::getInt(0, static_cast<int>(individual.size() - 1));
        individual.at(idx) = individual.at(idx) ? 0 : 1;
    }
}

#endif //TASK5_MUTATE_H