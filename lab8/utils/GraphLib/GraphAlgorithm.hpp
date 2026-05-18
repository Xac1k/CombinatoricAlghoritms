#pragma once
#include <algorithm>
#include <unordered_map>
#include <set>
#include <stack>
#include <queue>

#include "Graph.hpp"

using TimeMark = std::pair<size_t, std::pair<int, int>>;
using ListOfTimeMarks = std::unordered_map<size_t, std::pair<int, int>>;
using ListStrongBindingComponents = std::vector<std::vector<size_t>>;

template <typename T>
ListOfTimeMarks DFSTimeMarking(const Graph<T>& graph) noexcept {
    if(graph.Size() == 0) 
        return ListOfTimeMarks({});
    if(graph.Size() == 1)
        return ListOfTimeMarks({{0, {1, 2}}});

    std::set<size_t> ProcessedVertex{};
    std::stack<size_t> stackOfVertex{};
    stackOfVertex.push(0);
    ListOfTimeMarks timeMark{};
    size_t timer = 0;
    
    while(!stackOfVertex.empty()) {
        size_t currentVertex = stackOfVertex.top();
        
        if(!std::ranges::any_of(graph.GetOutputs(currentVertex),[&ProcessedVertex](const size_t& x){return !ProcessedVertex.contains(x); })) {
            timeMark[currentVertex].second = timer++;
            stackOfVertex.pop();
            ProcessedVertex.insert(currentVertex);
            
            if(stackOfVertex.empty()) {
                for(size_t i = 0; i < graph.Size(); i++){
                    if(!ProcessedVertex.contains(i)) {
                        stackOfVertex.push(i);
                        break;
                    }
                }
            }

            continue;
        }
    
        ProcessedVertex.insert(currentVertex);
        timeMark[currentVertex].first = timer++;
        
        std::vector<size_t> outputsWithProcessed = graph.GetOutputs(currentVertex);
        auto it = std::ranges::find_if(outputsWithProcessed, [&ProcessedVertex](const size_t& x){
            return !ProcessedVertex.contains(x); 
        });
        if(it != outputsWithProcessed.end()) stackOfVertex.push(*it);
    }
    return timeMark;
}

template <typename T>
ListStrongBindingComponents DFSBindingComponents(const Graph<T>& graph, std::queue<size_t> order) {
    if(graph.Size() == 0) 
        return ListStrongBindingComponents({});
    if(graph.Size() != order.size())
        throw std::invalid_argument("Number of vertex in graph and in order mismatch.");
    if(graph.Size() == 1)
        return ListStrongBindingComponents({{0}});

    std::set<size_t> ProcessedVertex{};
    std::stack<size_t> stackOfVertex{};
    ListStrongBindingComponents res{};

    while(!order.empty()) {
        if(ProcessedVertex.contains(order.front())) {
            order.pop();
            continue;
        }
           
        res.push_back({});
        stackOfVertex.push(order.front()); order.pop(); 
        
        while(!stackOfVertex.empty()) {
            int currentVertex = stackOfVertex.top();
            if(ProcessedVertex.contains(currentVertex)) {
                stackOfVertex.pop();
                continue;
            }

            ProcessedVertex.insert(currentVertex);
            res[res.size()-1].push_back(currentVertex);

            std::vector<size_t> outputsWithProcessed = graph.GetOutputs(currentVertex);
            std::ranges::reverse(outputsWithProcessed);
            std::ranges::for_each(outputsWithProcessed,
            [&ProcessedVertex,&stackOfVertex](const size_t& x){
                if(!ProcessedVertex.contains(x))
                    stackOfVertex.push(x);
            });
        }
    }

    return res;
}

struct CompareExitingTime {
    bool operator()(const TimeMark& a, const TimeMark& b) const {
        return a.second.second < b.second.second;
    }
};

template <typename T>
ListStrongBindingComponents GetStrongBindingComponents(Graph<T>& graph) noexcept {
    auto timeMarks = DFSTimeMarking(graph);

    std::priority_queue<TimeMark, std::vector<TimeMark>, CompareExitingTime> reductionOrderTimeMarks{};
    std::ranges::for_each(timeMarks, [&reductionOrderTimeMarks](const TimeMark& elt){
        reductionOrderTimeMarks.push(elt); 
    });

    std::queue<size_t> pq;
    while (!reductionOrderTimeMarks.empty()) {
        pq.push(reductionOrderTimeMarks.top().first);
        reductionOrderTimeMarks.pop();
    }

    graph.Transponate();
    ListStrongBindingComponents res =  DFSBindingComponents(graph, pq);
    graph.Transponate();
    return res;
}

template <typename T>
inline void SwapLines(size_t source, size_t dist, Graph<T>& graph) noexcept {
    for (size_t i = 0; i < graph.Size(); i++) {
        auto tmpSource = graph.GetVertex(i, source);
        auto tmpDist = graph.GetVertex(i, dist);
        if (tmpDist.isNull || tmpSource.isNull)
            continue;

        graph.SetVertex(i, dist, tmpSource.content);
        graph.SetVertex(i, source, tmpDist.content);
    }
}

inline void UpdateLinesBeforeEnd(size_t y, const size_t x, const std::function<float(float val)>& updater,  Graph<float>& graph) {
    for (size_t i = x; i < graph.Size(); i++) {
        const float rowICell = graph.GetVertex(i, y).content;
        graph.SetVertex(i, y, updater(rowICell));
    }
}

inline double CalculateDetermine(const Graph<float>& graph) noexcept {
    double determine = 1;
    Graph<float> res = graph;

    // Меняем значения
    for (size_t line = 0; line < res.Size(); line++) {
        if (res.GetVertex(line, line).content == 0) { // По диагонали ноль
            for (size_t yr = line + 1; yr < res.Size(); yr++) { // Поиск не нулевой
                if (res.GetVertex(line, yr).content != 0) {
                    SwapLines(yr, line, res);
                    determine *= -1;
                    break;
                }
            }
        }
        const auto diag = line;
        if (res.GetVertex(diag, diag).content == 0) return 0;

        // Приводим в треугольный вид
        for (size_t j = diag + 1; j < res.Size(); j++) {
            const float multiplier = res.GetVertex(diag, j).content / res.GetVertex(diag, diag).content;

            for (size_t xr = diag; xr < res.Size(); xr++) {
                const float rowICell = res.GetVertex(xr, diag).content;
                const float currentVal = res.GetVertex(xr, j).content;
                const float resultCell = currentVal - rowICell * multiplier;
                res.SetVertex(xr, j, resultCell);
            }
        }
    }

    for (size_t line = 0; line < res.Size(); line++)
        determine *= res.GetVertex(line, line).content;

    return determine;
}
