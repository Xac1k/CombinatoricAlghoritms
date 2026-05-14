//
// Created by xac1k on 4/13/26.
//

#ifndef TASK5_KROSSINGOVER_H
#define TASK5_KROSSINGOVER_H
#include "types.h"
#include "rand.h"

inline std::tuple<Individual, Individual> ExchangeGen(Individual& individual1, Individual& individual2, const int from) {
    for (int i = from; i < individual1.size(); i++)
        std::swap(individual1[i], individual2[i]);

    return std::make_tuple(individual1, individual2);
}

inline std::tuple<Individual, Individual> CrossOver(const Individual& parent1, const Individual& parent2, const double rate) {
    Individual son1 = parent1;
    Individual son2 = parent2;
    if (randFloat() <= rate) {
        const int idx = Random::getInt(0, static_cast<int>(parent1.size()) - 2); // [0, n-1]
        return ExchangeGen(son1, son2, idx);
    }

    return std::make_tuple(son1, son2);
}

#endif //TASK5_KROSSINGOVER_H