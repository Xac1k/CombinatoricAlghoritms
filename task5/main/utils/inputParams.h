//
// Created by xac1k on 4/14/26.
//

#ifndef TASK5_INPUTPARAMS_H
#define TASK5_INPUTPARAMS_H
#include <iostream>
#include <tuple>
#include <vector>

#include "types.h"

inline std::string Trim(std::string line) {
    std::string res;

    for (auto ch : line) {
        if (ch >= '0' && ch <= '9') {
            res = res + ch;
        }
    }
    return res;
}

std::tuple<std::vector<Item>, float> InputParams() {
    std::vector<Item> items;
    std::cout << "Enter the weights and costs of items inline in format '(n, c)'. Enter 'q' for end: " << std::endl;

    std::string input = "";
    while (std::cin >> input) {
        Item item;
        if (input == "q") break;

        float weight = std::stof(Trim(input));
        item.volume = weight;

        std::cin >> input;
        float cost = std::stof(Trim(input));
        item.cost = cost;
        items.push_back(item);
    }

    std::cout << "Enter limitations by weight: " << std::endl;
    float limitations;
    std::cin >> limitations;

    return std::make_tuple(items, limitations);
}

#endif //TASK5_INPUTPARAMS_H