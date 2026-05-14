//
// Created by xac1k on 4/12/26.
//

#ifndef TASK5_WEIGHT_H
#define TASK5_WEIGHT_H
#include "types.h"

inline double GetCost(const Individual& individual, const std::vector<Item>& characteristics) {
    double generalCost = 0;

    size_t itemID = 0;
    for (const auto& item : individual) {
        generalCost += (item & 0x1) * characteristics[itemID].cost;
        itemID++;
    }

    return generalCost;
}

inline double GetVolume(const Individual& individual, const std::vector<Item>& characteristics) {
    double generalVolume = 0;

    size_t itemID = 0;
    for (const auto& item : individual) {
        generalVolume += (item & 0x1) * characteristics[itemID].volume;
        itemID++;
    }

    return generalVolume;
}

#endif //TASK5_WEIGHT_H