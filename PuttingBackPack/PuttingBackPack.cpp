// PuttingBackPack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

bool NextOccurence(std::vector<size_t>& occurence) {
    size_t size = occurence.size();
    if (size == 0) return false;

    size_t idx = 0;
    while (idx != size && occurence[idx] == 1) {
        occurence[idx] = 0;
        idx++;
    }

    if (idx == size) return false;
    occurence[idx] = 1;

    return true;
}

void PrintVector(std::vector<size_t> vect) {
    std::string res = "";
    for (auto num : vect) {
        res = res + static_cast<char>('0' + num) + " ";
    }
    std::cout << res;
}

std::tuple<float, float> GetTotal(std::vector<size_t> occurence, std::vector<float> items, std::vector<float> costs) {
    if (occurence.size() != items.size()) 
        throw std::runtime_error("occurence size doesn't match with items size");

    float totalWeigth = 0, totalCost = 0;
    for (int i = 0; i < occurence.size(); i++) {
        if (occurence[i] == 1) {
            if (totalWeigth > FLT_MAX - items[i] || totalCost > FLT_MAX - costs[i])
                throw std::runtime_error("Reaches a FLT_MAX corner. Overflow.");
            totalWeigth += items[i];
            totalCost += costs[i];
        }
    }
    return std::make_tuple(totalWeigth, totalCost);
}

std::string Trim(std::string line) {
    std::string res;

    for (auto ch : line) {
        if (ch >= '0' || '9' <= ch) {
            res = res + ch;
        }
    }
    return res;
}

std::tuple<std::vector<float>, std::vector<float>, std::vector<size_t>, float> InputParams() {
    std::vector<float> items, costs;
    std::vector<size_t> occurence;

    std::cout << "Enter the weights and costs of items inline in format '(n, c)'. Enter 'q' for end: " << std::endl;
    
    std::string input = "";
    while (std::cin >> input) {
        if (input == "q") break;

        float weight = std::stof(Trim(input));
        items.push_back(weight);

        std::cin >> input;
        float cost = std::stof(Trim(input));
        costs.push_back(cost);
        
        occurence.push_back(0);
    }

    std::cout << "Enter limitations by weight: " << std::endl;
    float limitations;
    std::cin >> limitations;

    return std::make_tuple(items, costs, occurence, limitations);
}

std::tuple<float, float, std::vector<size_t>> SearhMaxComb(std::vector<float> items, std::vector<float> costs, std::vector<size_t> occurence, float limitations) {
    std::vector<size_t> maxOccurence;
    float maxWeight = -FLT_MAX, maxCost = -FLT_MAX;;
    do {
        auto [weight, cost] = GetTotal(occurence, items, costs);
        if (weight > limitations) continue;
        if (cost > maxCost) {
            maxOccurence = occurence;
            maxWeight = weight;
            maxCost = cost;
        }
    } while (NextOccurence(occurence));
    return std::make_tuple(maxWeight, maxCost, maxOccurence);
}

int main()
{
    try {
        auto [items, costs, occurence, limitations] = InputParams();
        auto [weight, maxCost, maxOccurence] = SearhMaxComb(items, costs, occurence, limitations);
   
        if (weight == 0)
            throw std::runtime_error("There isn't combinations for packing with limitations.");
        std::cout << "Result weigth: " << weight << std::endl << "Result cost: " << maxCost << std::endl;
        PrintVector(maxOccurence);
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}