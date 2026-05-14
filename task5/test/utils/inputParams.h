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

std::tuple<std::vector<float>, std::vector<float>, float> InputParams() {
    std::vector<float> items, costs;

    std::cout << "Enter the weights and costs of items inline in format '(n, c)'. Enter 'q' for end: " << std::endl;

    std::string input = "";
    while (std::cin >> input) {
        if (input == "q") break;

        float weight = std::stof(Trim(input));
        items.push_back(weight);

        std::cin >> input;
        float cost = std::stof(Trim(input));
        costs.push_back(cost);

    }

    std::cout << "Enter limitations by weight: " << std::endl;
    float limitations;
    std::cin >> limitations;

    return std::make_tuple(items, costs, limitations);
}

#endif //TASK5_INPUTPARAMS_H