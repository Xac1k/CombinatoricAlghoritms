#pragma once
#include "File.hpp"
#include "Graph.hpp"
#include "string.hpp"
#include <optional>
#include <functional>

template <typename T>
using Parser = std::function<std::optional<T>(const std::string&)>;

inline std::optional<int> ParseInt(std::string cell) {
    Trim(cell);
    if(cell == "-") return std::nullopt;
    return std::stoi(cell);
}

inline std::optional<float> ParseFloat(const std::string& cell) {
    if(cell == "-") return std::nullopt;
    return std::stof(cell);
}

template <typename T>
class GraphReader {
private:
    static bool IsSquareMatrix(const AgileMatrix<std::string>& matrix);

    static std::vector<std::string> Separate(const std::string& line, char delimiter);

    static AgileMatrix<std::string> ParseFileToStrMatrix(const std::string& rpath);
    static Graph<T> ConvertStringViewToGraph(const AgileMatrix<std::string>& matrix, const Parser<T>& parser);
public:
    static Graph<T> ReadFromFile(const std::string& rpath, const Parser<T>& parser);
};

template <typename T>
std::vector<std::string> GraphReader<T>::Separate(const std::string& line, char delimiter) {
    std::vector<std::string> result;
    std::string current;
    int depth = 0;

    for (const char c : line) {
        if (c == '{') {
            depth++;
            current += c;
        } else if (c == '}') {
            depth--;
            current += c;
        } else if (c == delimiter && depth == 0) {
            result.push_back(current);
            current.clear();
        } else {
            current += c;
        }
    }

    if (!current.empty())
        result.push_back(current);

    return result;
}

template <typename T>
Graph<T> GraphReader<T>::ConvertStringViewToGraph(const AgileMatrix<std::string>& matrix, const Parser<T>& parser) {
    size_t size = matrix.size();
    Graph<T> graph;
    graph.Resize(size);
    for(int y = 0; y < size; y++) {
        for(int x = 0; x < size; x++) {
            std::optional<T> cell = parser(matrix[y][x]);
            if(cell.has_value()) graph.SetVertex(x, y, cell.value());
            else graph.SetVertexNull(x, y);
        }
    }
    return graph;
}

template <typename T>
AgileMatrix<std::string> GraphReader<T>::ParseFileToStrMatrix(const std::string& rpath) {
    std::ifstream iFile;
    OpenFile(rpath, iFile);

    std::string line;
    std::getline(iFile, line);
    if (line != "matrix" && line != "list") 
        throw std::invalid_argument("unknown format of file");

    AgileMatrix<std::string> tmpMatrix;
    if(line == "matrix") {
        std::string tmpLine;
        while(std::getline(iFile, tmpLine)) {
            auto values = Separate(tmpLine, ',');
            tmpMatrix.push_back(values);
        }
    }
    else if (line == "list") {
        std::getline(iFile, line);
        size_t countNode = 0;
        try {
            countNode = std::stoull(line);
        }
        catch([[maybe_unused]] const std::exception& e) {
            throw std::invalid_argument("Second line need to be width of matrix type of int.");
        }
        
        tmpMatrix.resize(countNode, {});
        for(int y = 0; y < countNode; y++) tmpMatrix[y].resize(countNode, "-");
        
        while(std::getline(iFile, line)) {
            Trim(line);
            if(line.empty()) continue;

            auto values = Separate(line, ',');
            if(values.size() != 3) 
                throw std::invalid_argument("Invalid format of list");
            int y = std::stoull(values[0]);
            int x = std::stoull(values[1]);
            tmpMatrix[y][x] = values[3];
        }
    }
    else throw std::invalid_argument("Wrong Format");

    return tmpMatrix;
}

template <typename T>
Graph<T> GraphReader<T>::ReadFromFile(const std::string& rpath, const Parser<T>& parser) {
    const auto tmpMatrix = ParseFileToStrMatrix(rpath);
    if(!IsSquareMatrix(tmpMatrix))
        throw std::runtime_error("Matrix isn't square");
    return ConvertStringViewToGraph(tmpMatrix, parser);
}

template <typename T>
bool GraphReader<T>::IsSquareMatrix(const AgileMatrix<std::string>& matrix) {
    const size_t sizeY = matrix.size();

    for(int y = 0; y < sizeY; y++) {
        const auto sizeX = matrix[y].size();
        if(sizeX != sizeY)
            return false;
    }
    return true;
}