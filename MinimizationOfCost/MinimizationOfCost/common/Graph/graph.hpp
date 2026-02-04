#include <vector>
#define GRAPH_H
#ifndef TYPES_H
#include "../types.hpp"
#endif

class Graph
{
private:
    Matrix<int> graph;
public:
    Graph(Matrix<int> graphI);
    int getWeight(int source, int dist);
    int subtractWeight(int source, int dist, int deductible);
    int minPathWeight(List<int> path);
    Matrix<int> get();
    std::vector<int> getOutputs(int vertexID);
    std::vector<int> getInputs(int vertexID);
    int sizeX = 0;
    int sizeY = 0;
};

Graph::Graph(Matrix<int> graphI) : graph(graphI) {
    sizeY = graph.size(); // equal row
    if(sizeY != 0) {
        sizeX = graph[0].size(); // equal column
    }
}

int Graph::getWeight(int source, int dist) {
    int sizeY = graph.size();
    int sizeX = graph[0].size();

    if (source > sizeY - 1) return 0;
    if (dist > sizeX - 1) return 0;
    return graph[source][dist];
}

int Graph::subtractWeight(int source, int dist, int deductible) {
    int sizeY = graph.size();
    int sizeX = graph[0].size();

    if (source > sizeY - 1) return -1;
    if (dist > sizeX - 1) return -1;
    if (graph[source][dist] - deductible < 0) return -1;
    graph[source][dist] -= deductible;
    return graph[source][dist];
}

std::vector<int> Graph::getOutputs(int vertexID) {
    int sizeY = graph.size();
    int sizeX = graph[0].size();
    std::vector<int> outputs;
    if (vertexID > sizeY - 1) return outputs;

    for (int i = 0; i < sizeX; i++)
    {
        if (graph[vertexID][i]) outputs.push_back(i);
    }

    return outputs;
}

std::vector<int> Graph::getInputs(int vertexID) {
    int sizeY = graph.size();
    int sizeX = graph[0].size();

    std::vector<int> outputs;
    if (vertexID > sizeX - 1) return outputs;
    for (int i = 0; i < sizeY; i++)
    {
        if (graph[i][vertexID]) outputs.push_back(i);
    }

    return outputs;
}

Matrix<int> Graph::get() {
    return graph;
}

int Graph::minPathWeight(List<int> path) {
    int size = path.size();
    int distID = path[0];
    int minWeight = INT32_MAX;
    for (int i = 1; i < size; i++) {
        int w = getWeight(path[i], distID);
        if (minWeight > w) minWeight = w;
        distID = path[i];
    }
    return minWeight;
}