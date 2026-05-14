#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>

#include "../lib/GraphAlgorithm.hpp"
#include "../lib/Graph.hpp"
#include "../lib/GraphReader.hpp"

using namespace Catch::Matchers;

TEST_CASE("Проверка GraphReader") {
    GraphReader<int> ReaderIntGraph;  
    REQUIRE_THROWS(ReaderIntGraph.ReadFromFile("../in/2x1.txt", ParseInt));
    REQUIRE_THROWS(ReaderIntGraph.ReadFromFile("../in/wrong_format.txt", ParseInt));
    REQUIRE_THROWS(ReaderIntGraph.ReadFromFile("../in/wrong_type.txt", ParseInt));
    REQUIRE_THROWS(ReaderIntGraph.ReadFromFile("../in/wrong_list1.txt", ParseInt));
    REQUIRE_THROWS(ReaderIntGraph.ReadFromFile("../in/wrong_list2.txt", ParseInt));
    REQUIRE_THROWS(ReaderIntGraph.ReadFromFile("../in/wrong_index.txt", ParseInt));

    REQUIRE_NOTHROW(ReaderIntGraph.ReadFromFile("../in/0x0_null.txt", ParseInt));
    REQUIRE_NOTHROW(ReaderIntGraph.ReadFromFile("../in/1x1_cycle.txt", ParseInt));
    REQUIRE_NOTHROW(ReaderIntGraph.ReadFromFile("../in/1x1_empty.txt", ParseInt));
    REQUIRE_NOTHROW(ReaderIntGraph.ReadFromFile("../in/3x3_randomCycle.txt", ParseInt));
    REQUIRE_NOTHROW(ReaderIntGraph.ReadFromFile("../in/4x4_oneCycle.txt", ParseInt));
    REQUIRE_NOTHROW(ReaderIntGraph.ReadFromFile("../in/5x5_treeGraph.txt", ParseInt));
    REQUIRE_NOTHROW(ReaderIntGraph.ReadFromFile("../in/6x6_condensated.txt", ParseInt));
    REQUIRE_NOTHROW(ReaderIntGraph.ReadFromFile("../in/8x8_random.txt", ParseInt));
    REQUIRE_NOTHROW(ReaderIntGraph.ReadFromFile("../in/14x14_lect.txt", ParseInt));
}

TEST_CASE("Проверка DFS Strong Component Search") {
    GraphReader<int> ReaderIntGraph;  
    auto null = ReaderIntGraph.ReadFromFile("../in/0x0_null.txt", ParseInt);
    auto oneCycle = ReaderIntGraph.ReadFromFile("../in/1x1_cycle.txt", ParseInt);
    auto empty = ReaderIntGraph.ReadFromFile("../in/1x1_empty.txt", ParseInt);
    auto random3x3 = ReaderIntGraph.ReadFromFile("../in/3x3_randomCycle.txt", ParseInt);
    auto cycle4x4 = ReaderIntGraph.ReadFromFile("../in/4x4_oneCycle.txt", ParseInt);
    auto tree5x5 = ReaderIntGraph.ReadFromFile("../in/5x5_treeGraph.txt", ParseInt);
    auto condensated6x6 = ReaderIntGraph.ReadFromFile("../in/6x6_condensated.txt", ParseInt);
    auto random8x8 = ReaderIntGraph.ReadFromFile("../in/8x8_random.txt", ParseInt);
    auto lect14x14 = ReaderIntGraph.ReadFromFile("../in/14x14_lect.txt", ParseInt);
    
    SECTION("Тестирование exceptions функции GetStrongBindingComp") {
        REQUIRE_NOTHROW(GetStrongBindingComponents(null));
        REQUIRE_NOTHROW(GetStrongBindingComponents(oneCycle));
        REQUIRE_NOTHROW(GetStrongBindingComponents(empty));
        REQUIRE_NOTHROW(GetStrongBindingComponents(random3x3));
        REQUIRE_NOTHROW(GetStrongBindingComponents(cycle4x4));
        REQUIRE_NOTHROW(GetStrongBindingComponents(tree5x5));
        REQUIRE_NOTHROW(GetStrongBindingComponents(condensated6x6));
        REQUIRE_NOTHROW(GetStrongBindingComponents(random8x8));
        REQUIRE_NOTHROW(GetStrongBindingComponents(lect14x14));
    }

    SECTION("Тестирование ответов функции GetStrongBindingComp"){
        auto answer = GetStrongBindingComponents(null);
        CHECK_THAT(answer, Equals(ListStrongBindingComponents({})) );

        answer = GetStrongBindingComponents(oneCycle);
        CHECK_THAT(answer, Equals(ListStrongBindingComponents({{0}})) );

        answer = GetStrongBindingComponents(empty);
        CHECK_THAT(answer, Equals(ListStrongBindingComponents({{0}})) );

        answer = GetStrongBindingComponents(random3x3);
        CHECK_THAT(answer, Equals(ListStrongBindingComponents({{0}, {1}, {2}})) );

        answer = GetStrongBindingComponents(cycle4x4);
        CHECK_THAT(answer, Equals(ListStrongBindingComponents({{0, 3, 2, 1}})) );

        answer = GetStrongBindingComponents(tree5x5);
        CHECK_THAT(answer, UnorderedEquals(ListStrongBindingComponents({{0}, {1}, {2}, {3}, {4}})) );

        answer = GetStrongBindingComponents(condensated6x6);
        CHECK_THAT(answer, UnorderedEquals(ListStrongBindingComponents({{0, 2, 1}, {3, 4}, {5}})) );

        answer = GetStrongBindingComponents(random8x8);
        CHECK_THAT(answer, UnorderedEquals(ListStrongBindingComponents({{0, 4, 5, 2, 1, 3, 6, 7}})) );

        answer = GetStrongBindingComponents(lect14x14);
        CHECK_THAT(answer, UnorderedEquals(ListStrongBindingComponents({{11}, {12}, {13}, {2, 4}, {7, 10, 9}, {0, 1, 3, 5}, {8}, {6}})) );
    }
}