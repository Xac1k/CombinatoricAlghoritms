//
// Created by xac1k on 4/12/26.
//

#ifndef TASK5_TYPES_H
#define TASK5_TYPES_H
#include <cstdint>
#include <vector>

using Individual = std::vector<uint8_t>;
using Population = std::vector<Individual>;
using FitnessVect = std::vector<double>;
using CountIndividualsNextGeneration = std::vector<double>;
using ParentsPairVect = std::vector<std::pair<size_t, size_t>>;
struct Item {
    double cost;
    double volume;
};

#endif //TASK5_TYPES_H
