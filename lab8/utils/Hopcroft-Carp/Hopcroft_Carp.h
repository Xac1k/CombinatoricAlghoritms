//
// Created by xac1k on 5/19/26.
//

#ifndef MAIN_HOPCROFT_CARP_H
#define MAIN_HOPCROFT_CARP_H
#include <unordered_map>
#include <vector>

#include "../GraphLib/Graph.hpp"

using MChain = std::vector<size_t>;
using SelectedPairs = std::pmr::unordered_map<size_t, size_t>;

SelectedPairs ComputeCompetePairsNetwork(const Graph<int>& g);


#endif //MAIN_HOPCROFT_CARP_H