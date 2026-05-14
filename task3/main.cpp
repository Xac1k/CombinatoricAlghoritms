#include "lib/Graph.hpp"
#include "lib/GraphReader.hpp"
#include "lib/GraphAlgorithm.hpp"

int main(int argc, char const *argv[])
{
    GraphReader<float> ReaderFloatGraph;
    auto graph = ReaderFloatGraph.ReadFromFile("Matrix.txt", ParseInt);
    auto strongsComponents = GetStrongBindingComponents(graph);

    for(int i = 0; i < strongsComponents.size(); i++) {
        for(int j = 0; j < strongsComponents[i].size(); j++) {
            std::cout << strongsComponents[i][j] + 1 << ", ";
        }
        std::cout << std::endl;
    }

    return 0;
}
