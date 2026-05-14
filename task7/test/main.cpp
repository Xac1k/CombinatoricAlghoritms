//
// Created by xac1k on 4/30/26.
//

#include <iostream>

#include "./utils/GraphLib/Graph.hpp"
#include "./utils/GraphLib/GraphReader.hpp"
#include "./utils/GraphLib/GraphAlgorithm.hpp"

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    const auto graph = GraphReader<float>::ReadFromFile("../in.txt", ParseFloat);
    const auto res = CalculateDetermine(graph);
    std::cout << "Детерминант матрицы: " << res << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Время выполнения: " << duration.count() << " мкс\n";
}
