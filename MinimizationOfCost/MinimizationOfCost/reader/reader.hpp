#ifndef TYPES_H 
    #include "../common/types.hpp"
#endif
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <stdexcept>

class Reader
{
private:
    std::string separator = ",";
public:
    Matrix<int> fileToMatrix(std::string path);
    std::string buildPath(std::string path, int levelsUp);
    Matrix<int> ListToMatrix(std::string path, int x, int y);
};

std::string Reader::buildPath(std::string path, int levelsUp = 0) {
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path targetPath = currentPath;

    // Поднимаемся на нужное количество уровней вверх
    for (int i = 0; i < levelsUp; i++) {
        targetPath = targetPath.parent_path();
    }

    // Добавляем целевой путь
    targetPath /= path;
    return targetPath.string();
}

Matrix<int> Reader::fileToMatrix(std::string path) {
    std::string fullpath = buildPath(path);
    std::ifstream file(fullpath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + fullpath);
    }

    std::vector<std::vector<int>> tempMatrix;
    std::string line;

    while (std::getline(file, line)) {
        std::vector<int> row;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, separator[0])) row.push_back(std::stoi(cell));

        if (!tempMatrix.empty() && row.size() != tempMatrix[0].size()) {
            throw std::runtime_error("Matrix is not square - row size mismatch");
        }

        tempMatrix.push_back(row);
    }

    file.close();

    if (!tempMatrix.empty() && tempMatrix.size() != tempMatrix[0].size()) {
        throw std::runtime_error("Matrix is not square - rows: " +
            std::to_string(tempMatrix.size()) +
            ", cols: " + std::to_string(tempMatrix[0].size()));
    }

    return tempMatrix;
}

Matrix<int> Reader::ListToMatrix(std::string path, int x, int y) {
    std::string fullpath = buildPath(path);
    std::ifstream file(fullpath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + fullpath);
    }

    std::vector<std::vector<int>> tempMatrix;
    for (int i = 0; i < y; i++) {
        std::vector<int> tempVect;
        for (int j = 0; j < x; j++) {
            tempVect.push_back(0);
        }
        tempMatrix.push_back(tempVect);
    }
    std::string line;

    while (std::getline(file, line)) {
        std::vector<int> row;
        std::stringstream data(line);
        std::string cell;
        char del = ' ';

        while (std::getline(data, cell, del)) row.push_back(std::stoi(cell));

        tempMatrix[row[0]][row[1]] = row[2];
    }

    file.close();
    return tempMatrix;
}