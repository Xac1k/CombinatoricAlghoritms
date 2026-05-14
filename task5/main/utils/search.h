//
// Created by xac1k on 4/13/26.
//

#ifndef TASK5_SEARCH_H
#define TASK5_SEARCH_H
#include <cfloat>

#include "types.h"

inline Individual SearchBest(const Population& population, const FitnessVect& fitnessVect) {
    double bestProbability = -DBL_MAX;
    Individual bestIndividual;

    size_t individualIndex = 0;
    for (const auto& prob : fitnessVect) {
        if (prob > bestProbability) {
            bestProbability = prob;
            bestIndividual = population[individualIndex];
        }
        individualIndex++;
    }

    return bestIndividual;
}

#endif //TASK5_SEARCH_H
