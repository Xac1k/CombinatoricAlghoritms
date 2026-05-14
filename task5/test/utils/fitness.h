//
// Created by xac1k on 4/12/26.
//

#ifndef TASK5_FITNESS_H
#define TASK5_FITNESS_H

#include <cmath>

#include "./types.h"
#include "./compute.h"

inline double SearchMaxPair(const Individual& individual,const std::vector<Item>& characteristics) {
    double result = 0.0;

    int itemID = 0;
    for (const auto& item : individual) {
        const double candidate = characteristics[itemID].cost / characteristics[itemID].volume;
        if (candidate > result)
            result = candidate;
        itemID++;
    }

    return result;
}

inline double ErrorFunc(const double currentVolume, const double limitations) {
    return currentVolume - limitations;
}

inline double Fitness(const Individual& individual,const std::vector<Item>& characteristics, const double capacity) {
    const double generalCost = GetCost(individual, characteristics);
    const double generalVolume = GetVolume(individual, characteristics);

    const double maxPair = SearchMaxPair(individual, characteristics);
    const double pen = std::log2(1 + maxPair * ErrorFunc(generalVolume, capacity));
    return generalCost - pen;
}

inline FitnessVect ComputeFitness(const Population& population, const std::vector<Item>& characteristics, const double capacity) {
    FitnessVect fitness;
    for (const auto& item : population) {
        const auto rate = Fitness(item, characteristics, capacity);
        fitness.push_back(rate);
    }

    return fitness;
}

inline double ComputeTotalFitness(const FitnessVect& fitness) {
    double totalFitness = 0.0;
    for (const auto& item : fitness)
        totalFitness += item;
    return totalFitness;
}

inline CountIndividualsNextGeneration ComputeNumberOfIndividualsOnNextGen(const Population& population, const std::vector<Item>& characteristics, const double capacity) {
    CountIndividualsNextGeneration res;

    const auto fitnessVect = ComputeFitness(population, characteristics, capacity);
    const auto meanFitness = ComputeTotalFitness(fitnessVect) / population.size();

    for (const auto& item : fitnessVect)
        res.push_back(item / meanFitness);

    return res;
}

#endif //TASK5_FITNESS_H