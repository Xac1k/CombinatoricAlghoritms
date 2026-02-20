// ConteinerVector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Task: Каждый элемент массива должен быть умножен на минимальный элемент исходного массива.
// Подсказка: используйте алгоритм std::min_element, чтобы найти минимальный элемент массива.

#define CATCH_CONFIG_MAIN
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include "conteinerVector.h"

std::vector<double> ReadNumbers() {
    std::vector<double> vect;
    std::string value;

    while (std::cin >> value) 
        vect.push_back(std::stod(value));

    return vect;
}

void ProcessNumbers(std::vector<double>& vect) {
    auto it = std::min_element(vect.begin(), vect.end());
    
    for (auto& elt : vect)
        elt *= *it;
}

void PrintSortedNumbers(const std::vector<double>& vect) {
    std::vector<double> sortedVect = vect;
    std::sort(sortedVect.begin(), sortedVect.end());
    
    for (const auto& elt : sortedVect) 
        std::cout << std::setprecision(3) << elt << " ";

    std::cout << std::endl;
}

int main()
{
    try {
        std::vector<double> vect = ReadNumbers();
        ProcessNumbers(vect);
        PrintSortedNumbers(vect);
    }
    catch (std::exception& e) {
        std::cout << "ERROR" << std::endl;
    }
    return 0;
}