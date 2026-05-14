//
// Created by xac1k on 4/4/26.
//

#include "./CTriangle.h"

#include <cmath>
#include <stdexcept>

using namespace std::literals;

double ComputeAreaByGeron(const double perimeter, const double a, const double b, const double c) {
    const double pp = perimeter/2;
    return std::sqrt(pp*(pp-a)*(pp-b)*(pp-c));
}

double CTriangle::GetPerimeter() const {
    if (!m_cachedPerimeter.has_value())
        m_cachedPerimeter = GetLengthSide(1) + GetLengthSide(2) + GetLengthSide(3);
    const auto res = m_cachedPerimeter.value();
    return res;
}

double CTriangle::GetArea() const {
    if (!m_cachedArea.has_value())
        m_cachedArea = ComputeAreaByGeron(GetPerimeter(), GetLengthSide(1), GetLengthSide(2), GetLengthSide(3));
    const auto res = m_cachedArea.value();
    return res;
}

std::string CTriangle::ToString() const {
    std::string res;

    res += "Треугольник\n";
    res += "Периметр: " + std::to_string(GetPerimeter()) + "\n";
    res += "Площадь: " + std::to_string(GetArea()) + "\n";

    res += "Цвет обводки: " + std::to_string(IShape::GetOutlineColor()) + "\n";
    res += "Ширина обводки: " + std::to_string(IShape::GetOutlineThickness()) + "\n";
    res += "Цвет заливки: " + std::to_string(ISolidShape::GetFillColor()) + "\n";
    res += "Точки: \n";
    res += GetVertex(1).ToString() + "\n";
    res += GetVertex(2).ToString() + "\n";
    res += GetVertex(1).ToString() + "\n";

    return res;
}

CPoint CTriangle::GetVertex(int VertexID) const {
    if (VertexID < 1 || VertexID > 3)
        throw std::out_of_range("CTriangle::GetVertex()");
    return m_vertexes[VertexID - 1];
}

void CTriangle::clearCache() const {
    m_cachedPerimeter = std::nullopt;
    m_cachedArea = std::nullopt;
    m_LengthSide1 = std::nullopt;
    m_LengthSide2 = std::nullopt;
    m_LengthSide3 = std::nullopt;
}

CTriangle& CTriangle::SetVertex(int VertexID, CPoint Vertex) {
    if (VertexID < 1 || VertexID > 3)
        throw std::out_of_range("CTriangle::SetVertex()");

    clearCache();
    m_vertexes[VertexID - 1] = Vertex;

    return *this;
}

double CTriangle::GetLengthSide(int SideID) const {
    switch (SideID) {
        case 1:
            if (!m_LengthSide1.has_value())
                m_LengthSide1 = CVector(GetVertex(1) - GetVertex(2)).dist();
            return m_LengthSide1.value();
        case 2:
            if (!m_LengthSide2.has_value())
                m_LengthSide2 = CVector(GetVertex(2) - GetVertex(3)).dist();
            return m_LengthSide2.value();
        case 3:
            if (!m_LengthSide3.has_value())
                m_LengthSide3 = CVector(GetVertex(3) - GetVertex(1)).dist();
            return m_LengthSide3.value();
        default:
            throw std::out_of_range("CTriangle::GetLengthSide()");
    }
}
