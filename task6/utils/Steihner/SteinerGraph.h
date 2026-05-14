//
// Created by xac1k on 5/14/26.
//

#pragma once
#include <vector>
#include "../Drawer/common/CPoint.h"

enum class NodeType { Terminal, SteinerPoint };

struct Node {
    size_t id;
    CPoint point;
    NodeType type;
};

struct Edge {
    size_t from;
    size_t to;
    double length;
};

struct Graph {
    std::vector<Node> nodes;
    std::vector<Edge> edges;
    double totalLength = 0.0;
};