//
// Created by xac1k on 4/19/26.
//

#ifndef MAIN_SHRINKPOPULATIONBYBESTINDIVIDUAL_H
#define MAIN_SHRINKPOPULATIONBYBESTINDIVIDUAL_H
#include <algorithm>
#include <queue>
#include <set>
#include <memory>

#include "types.h"

struct SetItemOfIndividual {
    size_t idxInPopulation;
    std::shared_ptr<Individual> ind;

    bool operator<(const SetItemOfIndividual& other) const {
        const auto lenFst = this->ind->size();
        const auto LenSnd = other.ind->size();
        if (lenFst < LenSnd)
            return true;
        if (lenFst > LenSnd)
            return false;
        for (size_t i = 0; i < lenFst; ++i) {
            if (this->ind->at(i) < other.ind->at(i))
                return true;
        }
        return false;
    }
};

inline void ShrinkPopulationByUniqueBest(Population& population, FitnessVect& fitnessVect, size_t targetCountPopulation) {
    std::set<SetItemOfIndividual> uniqueItems;
    for (size_t i = 0; i < population.size(); ++i)
        uniqueItems.insert(SetItemOfIndividual{i,
            std::make_shared<Individual>(population[i])});

    std::vector<SetItemOfIndividual> shrinkedPopulation(uniqueItems.begin(), uniqueItems.end());

    std::sort(shrinkedPopulation.begin(), shrinkedPopulation.end(),
    [&fitnessVect](const SetItemOfIndividual& a, const SetItemOfIndividual& b) {
        return fitnessVect[a.idxInPopulation] > fitnessVect[b.idxInPopulation];
    });

    if (shrinkedPopulation.size() > targetCountPopulation) {
        shrinkedPopulation.resize(targetCountPopulation);
    }

    while (shrinkedPopulation.size() < targetCountPopulation) {
        const size_t idx = Random::getInt(0, population.size() - 1);
        shrinkedPopulation.push_back(SetItemOfIndividual{idx,
            std::make_shared<Individual>(population[idx])});
    }

    Population newPopulation;
    for (const auto& item : shrinkedPopulation)
        newPopulation.push_back(population[item.idxInPopulation]);

    population = std::move(newPopulation);
}

#endif //MAIN_SHRINKPOPULATIONBYBESTINDIVIDUAL_H