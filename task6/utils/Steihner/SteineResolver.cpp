#include "./SteineResolver.h"

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <iostream>
#include <queue>
#include "Utils/Steiner.h"

CPoint IPoint::GetPoint() const {
    return m_point;
}

void IPoint::SetPoint(const CPoint p) {
    m_point = p;
}

void SteinerPoint::SetChild(const SharedPoint &p1, const SharedPoint &p2, const SharedPoint &p3) {
    m_p1 = p1;
    m_p2 = p2;
    m_p3 = p3;
}

void VirtualPoint::SetUnwrapping(const SharedSteinerPoint &sp) {
    m_unwrappingPoint = sp;
}

void Edge::SetStartPoint(CPoint p) {
    p1 = p;
}

void Edge::SetEndPoint(CPoint p) {
    p2 = p;
}

double Edge::GetLength() const {
    return CVector(p2 - p1).dist();
}

CPoint Edge::GetStartPoint() const {
    return p1;
}

CPoint Edge::GetEndPoint() const {
    return p2;
}

SteinerPoint::SharedPoint SteinerPoint::GetChild(const short id) {
    if (id == 1) return m_p1;
    if (id == 2) return m_p2;
    if (id == 3) return m_p3;

    throw std::out_of_range("");
}

VirtualPoint::SharedSteinerPoint VirtualPoint::GetUnwrapping() {
    return m_unwrappingPoint;
}

std::tuple<DegeneratedPoint::SharedPoint, DegeneratedPoint::SharedPoint> DegeneratedPoint::GetUnwrapping() {
    return std::make_tuple(m_p1, m_p2);
}

void DegeneratedPoint::SetUnwrapping(const SharedPoint &p1, const SharedPoint &p2) {
    m_p1 = p1;
    m_p2 = p2;
}

CPoint DegeneratedPoint::GetPoint() const {
    return m_p->GetPoint();
}

void DegeneratedPoint::SetPoint(const SharedPoint &p) {
    m_p = p;
}

PointType DegeneratedPoint::GetTypeParent() const {
    return m_p->GetType();
}



template <typename T>
std::shared_ptr<T> GetShared(const T& item) {
    return std::make_shared<T>(item);
}

template <typename T>
bool IsNullOpt(std::optional<T> item) {
    return !item.has_value();
}

double angleAt(const CPoint& vertex, const CPoint& a, const CPoint& b) {
    CVector v1 = a - vertex;
    CVector v2 = b - vertex;
    double dot = v1.x * v2.x + v1.y * v2.y;
    double mag = v1.dist() * v2.dist();
    return std::acos(dot / mag) * 180.0 / M_PI;
}

int findMiddle(const CPoint& p1, const CPoint& p2, const CPoint& p3) {
    double a1 = angleAt(p1, p2, p3);
    double a2 = angleAt(p2, p1, p3);
    double a3 = angleAt(p3, p1, p2);
    if (a1 >= a2 && a1 >= a3) return 1;
    if (a2 >= a1 && a2 >= a3) return 2;
    return 3;
}




std::vector<std::tuple<size_t, size_t>> getCombinations(size_t n) {
    if (n < 1) return {};

    std::vector<std::tuple<size_t, size_t>> result;
    result.reserve((n + 1) * n * (n - 1) / 6);

    for (int i = 0; i <= n - 1; i++) {
        for (int j = i + 1; j <= n; j++) {
            result.emplace_back(i, j);
        }
    }

    return result;
}

std::vector<std::shared_ptr<Graph>> BuildAllPermutationsOfTask(const std::shared_ptr<Graph>& graph) {
    std::vector<std::shared_ptr<Graph>> result;
    std::vector<std::pair<size_t, std::shared_ptr<IPoint>>> filteredNodes = {};

    for (size_t counter = 0; const auto& node : graph->nodes) {
        if (node->GetType() != PointType::Steiner)
            filteredNodes.emplace_back(counter, node);
        counter++;
    }

    auto combinations = getCombinations(filteredNodes.size() - 1);
    for (const auto& [fir, sec] : combinations) {
        auto firstP = filteredNodes.at(fir);
        auto secondP = filteredNodes.at(sec);

        Graph g;
        g.mergeTask = {firstP.first, secondP.first};
        g.nodes = graph->nodes;
        g.edges = graph->edges;
        g.totalLength = graph->totalLength;
        result.push_back(GetShared(g));
    }

    return result;
}

std::queue<std::shared_ptr<Graph>> BuildInitialQueueTasks(std::vector<std::pair<size_t, CPoint>>& terminals) {
    Graph initialGraph;
    std::queue<std::shared_ptr<Graph>> tasks = {};

    for (const auto& [id, terminal] : terminals) {
        Terminal p; p.SetPoint(terminal);
        initialGraph.nodes.push_back(std::make_shared<Terminal>(p));
    }

    auto mergeTasks = BuildAllPermutationsOfTask(GetShared(initialGraph));
    for (const auto& task : mergeTasks) {
        tasks.push(task);
    }

    return tasks;
}

std::shared_ptr<Graph> BuildGraph(const std::shared_ptr<Graph>& graph) {
    Graph additionalGraph;

    additionalGraph.nodes = graph->nodes;
    additionalGraph.edges = graph->edges;
    additionalGraph.totalLength = graph->totalLength;

    additionalGraph.mergeTask = {0, 0};

    return std::make_shared<Graph>(additionalGraph);
}

void EraseMergedPoints(const std::shared_ptr<Graph>& graph, const std::tuple<size_t, size_t>& mergeTask) {
    auto [firstIdxP, secondIdxP] = mergeTask;

    if (firstIdxP > secondIdxP) {
        graph->nodes.erase(graph->nodes.begin() + static_cast<ptrdiff_t>(firstIdxP));
        graph->nodes.erase(graph->nodes.begin() + static_cast<ptrdiff_t>(secondIdxP));
    }
    else if (firstIdxP == secondIdxP) {
        graph->nodes.erase(graph->nodes.begin() + static_cast<ptrdiff_t>(firstIdxP));
    }
    else {
        graph->nodes.erase(graph->nodes.begin() + static_cast<ptrdiff_t>(secondIdxP));
        graph->nodes.erase(graph->nodes.begin() + static_cast<ptrdiff_t>(firstIdxP));
    }
}

template<typename T>
void EraseByPointer(const std::shared_ptr<Graph>& graph, const std::shared_ptr<T>& p) {
    size_t counter = 0;
    for (auto& node : graph->nodes) {
        if (node == p) break;
        counter++;
    }

    graph->nodes.erase(graph->nodes.begin() + static_cast<ptrdiff_t>(counter));
}

void ComputeLengthForDegeneratePoints(const std::shared_ptr<IPoint>& p, double& length) {
    if (p->GetType() == PointType::Degenerated) {
        auto dp = std::static_pointer_cast<DegeneratedPoint>(p);
        auto [p1, p2] = dp->GetUnwrapping();

        length += CVector(p1->GetPoint() - dp->GetPoint()).dist();
        length += CVector(p2->GetPoint() - dp->GetPoint()).dist();

        ComputeLengthForDegeneratePoints(p1, length);
        ComputeLengthForDegeneratePoints(p2, length);
    }
    if (p->GetType() == PointType::Virtual) {
        auto sp = std::static_pointer_cast<VirtualPoint>(p)->GetUnwrapping();
        ComputeLengthForDegeneratePoints(sp, length);
    }
    if (p->GetType() == PointType::Steiner) {
        auto st = std::static_pointer_cast<SteinerPoint>(p);

        ComputeLengthForDegeneratePoints(st->GetChild(1), length);
        ComputeLengthForDegeneratePoints(st->GetChild(2), length);
        ComputeLengthForDegeneratePoints(st->GetChild(3), length);
    }
}

void ComputeLengthsBy2Points(const std::vector<std::shared_ptr<Graph>> &graphs) {

    for (const auto& graph : graphs) {
        auto firstNode = graph->nodes.at(0);
        auto secondNode = graph->nodes.at(1);
        graph->totalLength = CVector(secondNode->GetPoint() - firstNode->GetPoint()).dist();
    }
}

std::shared_ptr<Graph> FindTheBestGraphByLength(const std::vector<std::shared_ptr<Graph>> &graphs) {
    if (graphs.empty())
        throw std::runtime_error("No graphs to compare");

    std::shared_ptr<Graph> bestGraph;
    auto length = DBL_MAX;

    for (const auto& graph : graphs) {
        if (graph->totalLength < length) {
            length = graph->totalLength;
            bestGraph = graph;
        }
    }
    return bestGraph;
}

std::shared_ptr<IPoint> HandleDegeneratedPoint(const std::shared_ptr<Graph>& newGraph, const std::shared_ptr<IPoint>& p1, const std::shared_ptr<IPoint>& p2, const std::shared_ptr<IPoint>& node) {
    DegeneratedPoint dp;
    switch (findMiddle(p1->GetPoint(), p2->GetPoint(), node->GetPoint())) {
        case 1:
            dp.SetPoint(p1);
            dp.SetUnwrapping(p2, node);
            EraseByPointer(newGraph, p2);
            EraseByPointer(newGraph, node);
            break;
        case 2:
            dp.SetPoint(p2);
            dp.SetUnwrapping(p1, node);
            EraseByPointer(newGraph, p1);
            EraseByPointer(newGraph, node);
            break;
        case 3:
            dp.SetPoint(node);
            dp.SetUnwrapping(p1, p2);
            EraseByPointer(newGraph, p1);
            EraseByPointer(newGraph, p2);
            break;
        default:;
    }
    return GetShared(dp);
}

std::tuple<std::shared_ptr<IPoint>, std::shared_ptr<IPoint>> GetPointFromMergeTask(const std::shared_ptr<Graph>& g) {
    auto [firstPIdx, secondPIdx] = g->mergeTask;
    if (firstPIdx > g->nodes.size() || secondPIdx > g->nodes.size())
        throw std::out_of_range("");

    auto firstP = g->nodes.at(firstPIdx);
    auto secondP = g->nodes.at(secondPIdx);
    return std::make_tuple(firstP, secondP);
}

int CountVirtualPoints(const std::shared_ptr<IPoint>& p1, const std::shared_ptr<IPoint>& p2, const std::shared_ptr<IPoint>& p3) {
    int res = 0;
    if (p1->GetType() == PointType::Virtual) res+=1;
    if (p2->GetType() == PointType::Virtual) res+=1;
    if (p3->GetType() == PointType::Virtual) res+=1;

    return res;
};

std::tuple<std::shared_ptr<IPoint>, std::shared_ptr<IPoint>> GetNotVirtual(const std::shared_ptr<IPoint>& p1, const std::shared_ptr<IPoint>& p2, const std::shared_ptr<IPoint>& p3) {
    if (p1->GetType() == PointType::Virtual) {
        return std::make_tuple(p2, p3);
    }
    if (p2->GetType() == PointType::Virtual) {
        return std::make_tuple(p1, p3);
    }
    if (p3->GetType() == PointType::Virtual) {
        return std::make_tuple(p1, p2);
    }
    throw std::logic_error("GetNotVirtual: all points are non-virtual");
}


void UnwrapPoint(std::vector<Edge>& edges, std::vector<std::shared_ptr<IPoint>>& resp, std::shared_ptr<IPoint> p) {
    if (p->GetType() == PointType::Terminal) {
        resp.push_back(p);
    }
    else if (p->GetType() == PointType::Steiner) {
        const auto sp = std::static_pointer_cast<SteinerPoint>(p);
        resp.push_back(sp);
        if (const int n = CountVirtualPoints(sp->GetChild(1), sp->GetChild(2), sp->GetChild(3)); n != 0) {
            if (n == 1) {
                resp.pop_back();
                auto [p1, p2] = GetNotVirtual(sp->GetChild(1), sp->GetChild(2), sp->GetChild(3));
                Edge e;
                e.SetStartPoint(p1->GetPoint());
                e.SetEndPoint(p2->GetPoint());
                edges.push_back(e);
                std::cout<<"AHTUNG";
            }
            if (n == 2) {
                resp.pop_back();
            }
        }

        UnwrapPoint(edges, resp, sp->GetChild(1));
        UnwrapPoint(edges, resp, sp->GetChild(2));
        UnwrapPoint(edges, resp, sp->GetChild(3));
    }
    else if (p->GetType() == PointType::Virtual) {
        auto vp = std::static_pointer_cast<VirtualPoint>(p);
        UnwrapPoint(edges, resp, vp->GetUnwrapping());
    }
    else if (p->GetType() == PointType::Degenerated) {
        auto dp = std::static_pointer_cast<DegeneratedPoint>(p);
        resp.push_back(dp);
        auto [p1, p2] = dp->GetUnwrapping();
        UnwrapPoint(edges, resp, p1);
        UnwrapPoint(edges, resp, p2);
    }
}

std::shared_ptr<Graph> UnwrapGraph(const std::shared_ptr<Graph>& graph) {
    if (graph->nodes.size() != 2)
        throw std::invalid_argument("To unwrap graph there need to be just two points");

    Graph unwrappedGraph;
    std::vector<std::shared_ptr<IPoint>> unwrappedPoints;
    std::vector<Edge> edges;

    UnwrapPoint(edges, unwrappedPoints, graph->nodes.at(0));
    UnwrapPoint(edges, unwrappedPoints, graph->nodes.at(1));

    for (const auto& p : unwrappedPoints)
        unwrappedGraph.nodes.push_back(p);

    unwrappedGraph.edges = edges;
    return GetShared(unwrappedGraph);
}



std::shared_ptr<Graph> FindOptimalTree(std::vector<std::pair<size_t, CPoint>>& terminals) {
    auto tasks = BuildInitialQueueTasks(terminals);
    std::vector<std::shared_ptr<Graph>> mergedGraphs;
    while (!tasks.empty()) {
        auto mergeTaskGraph = tasks.front();
        tasks.pop();
        auto [p1, p2] = GetPointFromMergeTask(mergeTaskGraph);

        for (const auto& node : mergeTaskGraph->nodes) {
            if (node == p1 || node == p2) continue;
            Steiner::Point steinerP{};
            auto newGraph = BuildGraph(mergeTaskGraph);

            try {
                steinerP = Steiner::GetSteinerPoint(p1->GetPoint(), p2->GetPoint(), node->GetPoint()).value();

                SteinerPoint sp;
                sp.SetPoint(steinerP.steinerPoint);
                sp.SetChild(p1, p2, node);

                VirtualPoint virP;
                virP.SetUnwrapping(GetShared(sp));
                virP.SetPoint(steinerP.from);

                EraseMergedPoints(newGraph, mergeTaskGraph->mergeTask);
                newGraph->nodes.push_back(std::make_shared<VirtualPoint>(virP));
            }
            catch (const OverlapNotExistError&) {continue;}
            catch (const AngleNotValidError&) {
                newGraph->nodes.push_back(HandleDegeneratedPoint(newGraph, p1, p2, node));
            }

            if (newGraph->nodes.size() < 3)
                mergedGraphs.push_back(newGraph);
            else {
                auto permutations = BuildAllPermutationsOfTask(newGraph);
                for (const auto& newTask : permutations)
                    tasks.push(newTask);
            }
        }
    }

    ComputeLengthsBy2Points(mergedGraphs);
    auto bestGraph = FindTheBestGraphByLength(mergedGraphs);
    return UnwrapGraph(bestGraph);;
};