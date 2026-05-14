//
// Created by xac1k on 4/19/26.
//

#ifndef MAIN_FILLNEWGEN_H
#define MAIN_FILLNEWGEN_H
#include <vector>

#include "fitness.h"
#include "types.h"

inline std::vector<Individual> FillNewGen(const std::vector<Individual>& population, const FitnessVect& fitnessVect) {
    std::vector<Individual> newGen;
    const auto countOfIndividualsInNewGen = ComputeNumberOfIndividualsOnNextGen(population, fitnessVect);


    for (size_t idx = 0; idx < population.size(); ++idx) {
        const int count = std::round(countOfIndividualsInNewGen.at(idx));
        for (int cnt = 0; cnt < count; ++cnt)
            newGen.push_back(population.at(idx));
    }

    return newGen;
}

#endif //MAIN_FILLNEWGEN_H
