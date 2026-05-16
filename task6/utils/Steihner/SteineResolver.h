// SteinerOptimalTreeFinder.h
#pragma once
#include <memory>

#include "../Drawer/common/CPoint.h"
#include <vector>
#include <utility>

class Edge {
public:
    void SetStartPoint(CPoint p);
    void SetEndPoint(CPoint p);
    [[nodiscard]] double GetLength() const;

    [[nodiscard]] CPoint GetStartPoint() const;
    [[nodiscard]] CPoint GetEndPoint() const;
private:
    CPoint p1 = {}, p2 = {};
};

enum class PointType{Terminal, Steiner, Virtual, Degenerated};
class IPoint {
public:
    IPoint() = default;
    virtual ~IPoint() = default;

    virtual PointType GetType()=0;
    [[nodiscard]] CPoint GetPoint() const;
    void SetPoint(CPoint p);
private:
    CPoint m_point = {0,0};
};

class Terminal : public IPoint {
public:
    PointType GetType() override { return PointType::Terminal; }

    Terminal() = default;
};

class SteinerPoint : public IPoint {
public:
    using SharedPoint = std::shared_ptr<IPoint>;
    PointType GetType() override { return PointType::Steiner; }
    void SetChild(const SharedPoint &p1, const SharedPoint &p2, const SharedPoint &p3);
    SharedPoint GetChild(short id);
private:
    SharedPoint m_p1, m_p2, m_p3;
};

class VirtualPoint : public IPoint {
public:
    using SharedSteinerPoint = std::shared_ptr<SteinerPoint>;
    PointType GetType() override { return PointType::Virtual; }
    void SetUnwrapping(const SharedSteinerPoint &sp);
    SharedSteinerPoint GetUnwrapping();
private:
    SharedSteinerPoint m_unwrappingPoint = {};
};

class DegeneratedPoint : public IPoint {
public:
    using SharedPoint = std::shared_ptr<IPoint>;
    PointType GetType() override { return PointType::Degenerated; }
    void SetUnwrapping(const SharedPoint &p1, const SharedPoint &p2);
    std::tuple<SharedPoint, SharedPoint> GetUnwrapping();
private:
    SharedPoint m_p1, m_p2;
};

struct Graph {
    std::vector<std::shared_ptr<IPoint>> nodes;
    std::vector<Edge> edges;
    std::tuple<size_t, size_t> mergeTask;

    double totalLength = 0.0;
};

std::shared_ptr<Graph> FindOptimalTree(std::vector<std::pair<size_t, CPoint>>& terminals);
