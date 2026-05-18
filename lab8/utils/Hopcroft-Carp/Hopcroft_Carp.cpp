//
// Created by xac1k on 5/19/26.
//

#include "Hopcroft_Carp.h"

#include <optional>

std::optional<std::pair<size_t, size_t>> FindInRightSide(const SelectedPairs& sp, size_t target) {
    for (auto pair: sp) {
        if (pair.second == target) {
            return pair;
        }
    }
    return std::nullopt;
}

std::optional<std::pair<size_t, size_t>> FindInLeftSide(const SelectedPairs& sp, size_t target) {
    for (auto pair: sp) {
        if (pair.first == target) {
            return pair;
        }
    }
    return std::nullopt;
}

SelectedPairs BuildInitialPairsNetwork(const Graph<int>& g) {
    SelectedPairs res;

    for (size_t idx = 0; idx < g.Size(); ++idx) {
        auto outputs = g.GetOutputs(idx);
        for (auto output: outputs) {
            auto target = FindInRightSide(res, output);
            if (!target.has_value()) {
                res.insert(std::make_pair(idx, output));
                break;
            }
        }
    }

    return res;
}

MChain FindMinimalMChain(const SelectedPairs& sp, size_t target) {
    MChain res;
}

SelectedPairs ComputeCompetePairsNetwork(const Graph<int>& g) {
    auto pairs = BuildInitialPairsNetwork(g);


    return pairs;
}
