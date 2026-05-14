//
// Created by xac1k on 4/13/26.
//

#ifndef TASK5_GENERATEPOPULATION_H
#define TASK5_GENERATEPOPULATION_H
#include "generateIndividual.h"
#include "types.h"

inline Population generatePopulation(const size_t number, size_t lenOfGen, double rate) {
    Population population;
    population.reserve(number);

    for (size_t i = 0; i < number; i++)
        population.push_back(generateIndividual(lenOfGen, rate));

    return population;
}

#endif //TASK5_GENERATEPOPULATION_H