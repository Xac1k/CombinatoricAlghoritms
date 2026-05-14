//
// Created by xac1k on 4/12/26.
//

#include <cassert>
#include <ctime>

#include "utils/crossover.h"
#include "utils/fitness.h"
#include "utils/generatePopulation.h"
#include "utils/repair.h"
#include "utils/search.h"
#include "utils/generateParentsPair.h"
#include "utils/mutate.h"
#include "utils/inputParams.h"
#include "utils/fillNewGen.h"
#include "utils/shrinkPopulationByBestIndividual.h"

constexpr int POPULATION_SIZE = 100;
constexpr double ONE_CORNER = 0.5;

constexpr double REPAIR_PERCENTAGE = 1;
constexpr double MUTATION_RATE = 0.01;
constexpr int MAX_GENERATIONS = 1500;
constexpr double CROSSOVER_RATE = 0.5;

void PrintVector(std::vector<uint8_t> vect) {
    std::string res = "";
    for (auto num : vect) {
        res = res + static_cast<char>('0' + num) + " ";
    }
    std::cout << res;
}

int main() {
    const auto [items, capacity] = InputParams();
    auto population = generatePopulation(POPULATION_SIZE, items.size(), ONE_CORNER);
    Repair(population, items, 1, capacity);

    for (int iter = 0; iter < MAX_GENERATIONS; iter++) {
        const auto fitnessVect = ComputeFitness(population, items, capacity);
        auto nextGeneration = FillNewGen(population, fitnessVect);
        nextGeneration.push_back(SearchBest(population, fitnessVect));
        const auto parentPairs = GenerateParentsPair(nextGeneration, POPULATION_SIZE / 2);

        for (const auto&[fst, snd] : parentPairs) {
            Individual &Parent1 = nextGeneration[fst];
            Individual &Parent2 = nextGeneration[snd];
            auto [son1, son2] = CrossOver(Parent1, Parent2, CROSSOVER_RATE);

            Mutate(son1, MUTATION_RATE);
            Mutate(son2, MUTATION_RATE);

            nextGeneration.push_back(son1);
            nextGeneration.push_back(son2);
        }
        Repair(nextGeneration, items, 1, capacity);
        population = std::move(nextGeneration);

        auto fitnessVectNextGen = ComputeFitness(population, items, capacity);
        ShrinkPopulationByUniqueBest(population, fitnessVectNextGen, POPULATION_SIZE);
    }
    const auto bestIndividual = SearchBest(population, ComputeFitness(population, items, capacity));
    const auto volume = GetVolume(bestIndividual, items);
    const auto cost = GetCost(bestIndividual, items);

    std::cout << "Result weight: " << volume << std::endl;
    std::cout << "Result cost: " << cost << std::endl;
    PrintVector(bestIndividual);
}