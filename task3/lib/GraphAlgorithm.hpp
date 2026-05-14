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
        
        std::vector<size_t> outputsWihtProcessed = graph.GetOutputs(currentVertex);
        auto it = std::ranges::find_if(outputsWihtProcessed, [&ProcessedVertex](const size_t& x){ 
            return !ProcessedVertex.contains(x); 
        });
        if(it != outputsWihtProcessed.end()) stackOfVertex.push(*it);
    }
    return timeMark;
}

template <typename T>
ListStrongBindingComponents DFSBindingComponents(const Graph<T>& graph, std::queue<size_t> order) {
    if(graph.Size() == 0) 
        return ListStrongBindingComponents({});
    if(graph.Size() != order.size())
        throw std::invalid_argument("Number of vertex in graph and in order mismath.");
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

            std::vector<size_t> outputsWihtProcessed = graph.GetOutputs(currentVertex);
            std::reverse(outputsWihtProcessed.begin(), outputsWihtProcessed.end());
            std::ranges::for_each(outputsWihtProcessed, 
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