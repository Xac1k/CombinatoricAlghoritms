//
// Created by xac1k on 4/14/26.
//

#ifndef TASK5_SELECTIONPARENTS_H
#define TASK5_SELECTIONPARENTS_H
#include <stdexcept>

#include "types.h"

inline size_t GetOneIndex(const CountIndividualsNextGeneration& probabilities) {
    if (probabilities.empty())
        throw std::out_of_range("Probabilities is an empty vect!");
    const auto chaoticNumber = randFloat();

    double lowBound = 0;
    double highBound = probabilities.at(0);

    size_t index = 0;
    while (!(lowBound <=  chaoticNumber && chaoticNumber <= highBound) && index < (probabilities.size() - 1)) {
        index++;
        lowBound = highBound;
        highBound += probabilities.at(index);
    }

    return index;
}

inline ParentsPairVect GenerateParentsPair(const CountIndividualsNextGeneration& probabilities, size_t countOfParents) {
    ParentsPairVect res;
    for (int i = 0; i < countOfParents; ++i) {
        const size_t firstParentIdx = GetOneIndex(probabilities);
        size_t secondParentIdx = GetOneIndex(probabilities);

        while (firstParentIdx == secondParentIdx) { secondParentIdx = GetOneIndex(probabilities); }
        res.emplace_back(firstParentIdx, secondParentIdx);
    }
    return res;
}

#endif //TASK5_SELECTIONPARENTS_H