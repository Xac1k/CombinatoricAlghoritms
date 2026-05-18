#pragma once
#include <exception>
#include <ostream>

#include "Types.h"

template <typename T>
class Graph
{
private:
    struct TypeCell {
        bool isNull = false;
        T content = T{};
    };

    AgileMatrix<TypeCell> m_matrix;
    size_t m_size = 0;

public:
    Graph();
    ~Graph() = default;
    //Vertex -> Vertex
    typename Graph<T>::TypeCell GetVertex(size_t source, size_t dist) const;
    void SetVertex(size_t x, size_t y, T Vertex);
    void SetVertexNull(size_t x, size_t y);
    void Resize(size_t size);
    void Transponate();
    std::vector<size_t> GetOutputs(size_t VertexID) const;
    std::vector<size_t> GetInputs(size_t VertexID) const;
    size_t Size() const;
};

template <typename T>
Graph<T>::Graph() {
    m_matrix = {};
    m_size = 0;
}

template <typename T>
size_t Graph<T>::Size() const {
    return m_size;
}

template <typename T>
void Graph<T>::SetVertex(size_t x, size_t y, T Vertex) {
    if(x < 0 || x >= m_size) 
        throw std::out_of_range("ID out of range");

    if(y < 0 || y >= m_size) 
        throw std::out_of_range("ID out of range");

    m_matrix[y][x].content = Vertex;
    m_matrix[y][x].isNull = false;
}

template <typename T>
void Graph<T>::SetVertexNull(size_t x, size_t y) {
    if(x < 0 || x >= m_size) 
        throw std::out_of_range("ID out of range");

    if(y < 0 || y >= m_size) 
        throw std::out_of_range("ID out of range");

    m_matrix[y][x].isNull = true;
}

template <typename T>
void Graph<T>::Resize(size_t size) {
    m_matrix.resize(size);
    m_size = size;

    for(auto& row : m_matrix) {
        row.resize(size);
    }
}

template <typename T>
typename Graph<T>::TypeCell Graph<T>::GetVertex(size_t x, size_t y) const {
    if(x < 0 || y < 0) 
        throw std::out_of_range("x and y must be non negative values");

    if(x >= m_size || y >= m_size)
        throw std::out_of_range("x and y must be less then " + std::to_string(m_size) + " for this object of class" );

    return m_matrix[y][x];
};

// Получает все номера не нулевых нод в графе по оси x вершины y.
template <typename T>
std::vector<size_t> Graph<T>::GetOutputs(size_t VertexID) const {
    if(VertexID < 0 || VertexID >= m_size) 
        throw std::out_of_range("ID out of range");

    std::vector<size_t> res;

    for(size_t id = 0; id < m_size; id++) {
        if(!m_matrix[VertexID][id].isNull) {
            res.push_back(id);
        }
    }

    return res;
}

template <typename T>
std::vector<size_t> Graph<T>::GetInputs(size_t VertexID) const {
    if(VertexID < 0 || VertexID >= m_size) 
        throw std::out_of_range("ID out of range");

    std::vector<size_t> res;
    for(size_t id = 0; id < m_size; id++) {
        if(!m_matrix[id][VertexID].isNull) {
            res.push_back(id);
        }
    }

    return res;
}

template <typename T>
void Graph<T>::Transponate() {
    for(size_t y = 0; y < m_size; y++) {
        for(size_t x = y + 1; x < m_size; x++)
            std::swap(m_matrix[y][x], m_matrix[x][y]);
    }
}