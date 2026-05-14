
//
// Created by xac1k on 4/14/26.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

using namespace Catch::Matchers;

#include "utils/crossover.h"
#include "utils/fitness.h"
#include "utils/generatePopulation.h"
#include "utils/repair.h"
#include "utils/search.h"
#include "utils/generateParentsPair.h"
#include "utils/mutate.h"
#include "utils/inputParams.h"

TEST_CASE("crossover") {
    SECTION("exchanging") {
        Individual parent1 = {0, 1, 1, 1, 0, 1};
        Individual parent2 = {1, 0, 0, 0, 1, 0};

        const auto [son1, son2] = ExchangeGen(parent1, parent2, 3);
        CHECK(son1 == Individual({0, 1, 1, 0, 1, 0}));
        CHECK(son2 == Individual({1, 0, 0, 1, 0, 1}));
    }
}

TEST_CASE("Computing") {
    SECTION("ComputingCost") {
        std::vector<Item> availableItems = {
            Item({.cost = 1, .volume = 7}),
            Item({.cost = 2, .volume = 8}),
            Item({.cost = 3, .volume = 9}),
            Item({.cost = 4, .volume = 10}),
            Item({.cost = 5, .volume = 11}),
            Item({.cost = 6, .volume = 12}),
        };

        Individual individual = {0, 1, 1, 1, 0, 1};
        CHECK(GetCost(individual, availableItems) == 15);
    }

    SECTION("ComputingVolume") {
        std::vector<Item> availableItems = {
            Item({.cost = 1, .volume = 7}),
            Item({.cost = 2, .volume = 8}),
            Item({.cost = 3, .volume = 9}),
            Item({.cost = 4, .volume = 10}),
            Item({.cost = 5, .volume = 11}),
            Item({.cost = 6, .volume = 12}),
        };

        Individual individual = {0, 1, 1, 1, 0, 1};
        CHECK(GetVolume(individual, availableItems) == 39);
    }

    SECTION("Search Best Pair") {
        std::vector<Item> availableItems = {
            Item({.cost = 1, .volume = 7}),
            Item({.cost = 2, .volume = 8}),
            Item({.cost = 3, .volume = 9}),
            Item({.cost = 4, .volume = 10}),
            Item({.cost = 5, .volume = 11}),
            Item({.cost = 6, .volume = 12}),
        };

        Individual individual = {0, 1, 1, 1, 0, 1};
        CHECK(SearchMaxPair(individual, availableItems) == 0.5);
    }

    SECTION("Fitness") {
        std::vector<Item> availableItems = {
            Item({.cost = 1, .volume = 7}),
            Item({.cost = 2, .volume = 8}),
            Item({.cost = 3, .volume = 9}),
            Item({.cost = 4, .volume = 10}),
            Item({.cost = 5, .volume = 11}),
            Item({.cost = 6, .volume = 12}),
        };

        Individual individualUnLimited = {1, 1, 1, 1, 1, 1};
        Individual individualLimited = {0, 0, 1, 1, 0, 0};
        const auto estimationUnsuitable = Fitness(individualUnLimited, availableItems, 20);
        const auto estimationSuitable = Fitness(individualLimited, availableItems, 20);

        CHECK(estimationUnsuitable <= estimationSuitable);
    }

    SECTION("ComputeFitness By Population") {
        std::vector<Item> availableItems = {
            Item({.cost = 1, .volume = 7}),
            Item({.cost = 2, .volume = 8}),
            Item({.cost = 3, .volume = 9}),
            Item({.cost = 4, .volume = 10}),
            Item({.cost = 5, .volume = 11}),
            Item({.cost = 6, .volume = 12}),
        };

        Individual individualUnLimited = {0, 1, 1, 1, 0, 1};
        Individual individualLimited = {0, 0, 1, 1, 0, 0};

        Population population = {individualLimited, individualUnLimited};
        const auto fitness = ComputeFitness(population, availableItems, 20);

        CHECK(fitness.size() == 2);
        CHECK(fitness.at(1) <= fitness.at(0));
    }

    SECTION("Survival Probability") {
        std::vector<Item> availableItems = {
            Item({.cost = 1, .volume = 7}),
            Item({.cost = 2, .volume = 8}),
            Item({.cost = 3, .volume = 9}),
            Item({.cost = 4, .volume = 10}),
            Item({.cost = 5, .volume = 11}),
            Item({.cost = 6, .volume = 12}),
        };

        Individual individualUnLimited = {0, 1, 1, 1, 0, 1};
        Individual individualLimited = {0, 0, 1, 1, 0, 0};

        Population population = {individualLimited, individualUnLimited};
        const auto survivalsCoefficients = ComputeNumberOfIndividualsOnNextGen(population, availableItems, 20);

        CHECK(survivalsCoefficients.size() == 2);
        CHECK(survivalsCoefficients.at(0) <= survivalsCoefficients.at(1));
    }

    SECTION("Search best") {
        std::vector<Item> availableItems = {
            Item({.cost = 1, .volume = 7}),
            Item({.cost = 2, .volume = 8}),
            Item({.cost = 3, .volume = 9}),
            Item({.cost = 4, .volume = 10}),
            Item({.cost = 5, .volume = 11}),
            Item({.cost = 6, .volume = 12}),
        };

        Individual individualUnLimited = {0, 1, 1, 1, 0, 1};
        Individual individualLimited = {0, 0, 1, 1, 0, 0};

        Population population = {individualLimited, individualUnLimited};
        const auto survivalsCoefficients = ComputeFitness(population, availableItems, 20);

        const auto bestIndividual = SearchBest(population, survivalsCoefficients);
        CHECK(bestIndividual == individualLimited);
    }
}

TEST_CASE("Filtering") {
    SECTION("Repair") {
        std::vector<Item> availableItems = {
            Item({.cost = 1, .volume = 7}),
            Item({.cost = 2, .volume = 8}),
            Item({.cost = 3, .volume = 9}),
            Item({.cost = 4, .volume = 10}),
            Item({.cost = 5, .volume = 11}),
            Item({.cost = 6, .volume = 12}),
        };

        Individual individual = {0, 1, 1, 1, 0, 1};
        double volumeLimit = 10;
        double initVolume = GetVolume(individual, availableItems);
        std::vector<Individual> population({individual});
        Repair(population, availableItems, 1, volumeLimit);
        double postRepairVolume = GetVolume(population.at(0), availableItems);

        CHECK((postRepairVolume <= volumeLimit && initVolume >= volumeLimit));
    }
}