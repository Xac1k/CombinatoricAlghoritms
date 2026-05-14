//
// Created by xac1k on 4/5/26.
//

#include "./CCircle.h"

#include <stdexcept>

double CCircle::GetArea() const {
    if (!m_cachedArea.has_value())
        m_cachedArea = std::numbers::pi * m_radius * m_radius;
    return m_cachedArea.value();
}

double CCircle::GetPerimeter() const {
    if (!m_cachedPerimeter.has_value())
        m_cachedPerimeter = 2 * std::numbers::pi * m_radius;
    return m_cachedPerimeter.value();
}

void CCircle::ClearCache() const {
    m_cachedPerimeter = std::nullopt;
    m_cachedArea = std::nullopt;
}

CPoint CCircle::GetPosition() const {
    return m_position;
}

CCircle &CCircle::SetRadius(double radius) {
    if (radius < 0)
        throw std::invalid_argument("radius must be non-negative");
    ClearCache();
    m_radius = radius;
    return *this;
}

double CCircle::GetRadius() const {
    return m_radius;
}

CCircle &CCircle::SetPosition(const CPoint &point) {
    m_position = point;
    return *this;
}

std::string CCircle::ToString() const {
    std::string res;

    res += "Круг\n";
    res += "Периметр: " + std::to_string(GetPerimeter()) + "\n";
    res += "Площадь: " + std::to_string(GetArea()) + "\n";

    res += "Цвет обводки: " + std::to_string(IShape::GetOutlineColor()) + "\n";
    res += "Ширина обводки: " + std::to_string(IShape::GetOutlineThickness()) + "\n";
    res += "Цвет заливки: " + std::to_string(ISolidShape::GetFillColor()) + "\n";
    res += "Позиция: " + std::to_string(m_position.x) + " " + std::to_string(m_position.y) + "\n";
    res += "Радиус: " + std::to_string(m_radius) + "\n";

    return res;
}
