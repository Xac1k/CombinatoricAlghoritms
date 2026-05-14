//
// Created by xac1k on 4/4/26.
//

#ifndef TESTS_CTRIANGLE_H
#define TESTS_CTRIANGLE_H
#include <array>

#include "../common/CPoint.h"
#include "ISolidShape.h"

class CTriangle : public ISolidShape {
public:
    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;

    CPoint GetVertex(int VertexID) const;
    CTriangle& SetVertex(int VertexID, CPoint Vertex);

private:
    std::array<CPoint, 3> m_vertexes = {};

    mutable std::optional<double> m_LengthSide1 = std::nullopt;
    mutable std::optional<double> m_LengthSide2 = std::nullopt;
    mutable std::optional<double> m_LengthSide3 = std::nullopt;
    double GetLengthSide(int SideID) const;
    void clearCache() const;
};


#endif //TESTS_CTRIANGLE_H