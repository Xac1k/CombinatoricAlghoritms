//
// Created by xac1k on 4/5/26.
//

#include "./CRectangle.h"

#include <stdexcept>

double CRectangle::GetArea() const {
    if (!m_cachedArea.has_value())
        m_cachedArea = m_size.x * m_size.y;
    return m_cachedArea.value();
}

double CRectangle::GetPerimeter() const {
    if (!m_cachedPerimeter.has_value())
        m_cachedPerimeter = m_size.x * 2 + m_size.y * 2;
    return m_cachedPerimeter.value();
}

void CRectangle::ClearCache() const {
    m_cachedPerimeter = std::nullopt;
    m_cachedArea = std::nullopt;
}

double CRectangle::GetHeight() const {
    return m_size.y;
}

double CRectangle::GetWidth() const {
    return m_size.x;
}

double CRectangle::GetRadius() const {
    return m_size.x;
}

CPoint CRectangle::GetPosition() const {
    return m_position;
}

CRectangle& CRectangle::SetPosition(const CPoint& point) {
    m_position = point;
    return *this;
}

CRectangle& CRectangle::SetHeight(double height) {
    if (height < 0)
        throw std::invalid_argument("The height must be non-negative value");
    ClearCache();
    m_size.y = height;
    return *this;
}

CRectangle& CRectangle::SetWidth(double width) {
    if (width < 0)
        throw std::invalid_argument("The width must be non-negative value");
    ClearCache();
    m_size.x = width;
    return *this;
}

std::string CRectangle::ToString() const {
    std::string res;

    res += "Прямоугольник\n";
    res += "Периметр: " + std::to_string(GetPerimeter()) + "\n";
    res += "Площадь: " + std::to_string(GetArea()) + "\n";

    res += "Цвет обводки: " + std::to_string(IShape::GetOutlineColor()) + "\n";
    res += "Ширина обводки: " + std::to_string(IShape::GetOutlineThickness()) + "\n";
    res += "Цвет заливки: " + std::to_string(ISolidShape::GetFillColor()) + "\n";
    res += "Позиция: " + std::to_string(m_position.x) + " " + std::to_string(m_position.y) + "\n";
    res += "Размеры: " + std::to_string(m_size.x) + " " + std::to_string(m_size.y) + "\n";

    return res;
}
