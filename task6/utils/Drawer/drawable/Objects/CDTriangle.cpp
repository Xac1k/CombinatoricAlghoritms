//
// Created by xac1k on 4/9/26.
//

#include "CDTriangle.h"
void CDTriangle::Draw(ICanvas &canvas) const {
    std::vector<CPoint> vertices = {};

    for (int i = 1; i < 4; i++)
        vertices.push_back(GetVertex(i));

    canvas.FillPolygon(vertices, GetFillColor());

    for (int i = 0; i < 3; i++)
        canvas.DrawLine(vertices.at(i), vertices.at((i + 1) % 3), GetOutlineColor(), GetOutlineThickness());
}
