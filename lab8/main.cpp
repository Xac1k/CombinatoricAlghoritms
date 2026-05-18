// =============================================
// Алгоритм Хопкрофта-Карпа
// Выполнено студентом 2 курса института iSpring
// Жуковым Максимом Игоревичем
// =============================================

#include "utils/GraphLib/Graph.hpp"
#include "utils/GraphLib/GraphReader.hpp"
#include "utils/Hopcroft-Carp/Hopcroft_Carp.h"

int main() {
    auto graph = GraphReader<int>::ReadFromFile("../input.txt", ParseInt);
    auto solution = ComputeCompetePairsNetwork(graph);

    return 0;
}

