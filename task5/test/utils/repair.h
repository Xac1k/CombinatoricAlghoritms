//
// Created by xac1k on 4/12/26.
//

#ifndef TASK5_REPAIR_H
#define TASK5_REPAIR_H

#include "rand.h"
#include "compute.h"
#include "types.h"

inline std::vector<size_t> GetOneIndexes(const Individual& individual) {
    std::vector<size_t> indexes;
    for (size_t i = 0; i < individual.size(); ++i) {
        if (individual.at(i) == 1) {
            indexes.push_back(i);
        }
    }
    return indexes;
}

inline void chaoticGettingThingsBeforeLimit(Individual& individual, const std::vector<Item>& items, const double capacity) {
    double volume = GetVolume(individual, items);
    while (capacity < volume) {
        std::vector<size_t> individualIdx = GetOneIndexes(individual);
        const size_t itemIDX = individualIdx[Random::getInt(0, static_cast<int>(individualIdx.size() - 1))];
        individual.at(itemIDX) = 0;
        volume -= items.at(itemIDX).volume;
    }
}

inline void Repair(std::vector<Individual>& population, const std::vector<Item>& items, const double repairPercentage, const double capacity) {
    for (auto& individual : population)
        if (capacity < GetVolume(individual, items))
            if (randFloat() <= repairPercentage)
                chaoticGettingThingsBeforeLimit(individual, items, capacity);
};

#endif //TASK5_REPAIR_H