//
// Created by xac1k on 4/5/26.
//

#include "./CLineSegment.h"

double CLineSegment::GetArea() const {
    return 0;
}

double CLineSegment::GetPerimeter() const {
    return CVector(m_startPoint - m_endPoint).dist();
}

CPoint CLineSegment::GetStartPoint() const {
    return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const {
    return m_endPoint;
}

CLineSegment &CLineSegment::SetStartPoint(CPoint point) {
    m_startPoint = point;
    return *this;
}

CLineSegment &CLineSegment::SetEndPoint(CPoint point) {
    m_endPoint = point;
    return *this;
}

std::string CLineSegment::ToString() const {
    std::string res;

    res += "Линия\n";
    res += "Периметр: " + std::to_string(GetPerimeter()) + "\n";

    res += "Цвет обводки: " + std::to_string(IShape::GetOutlineColor()) + "\n";
    res += "Ширина обводки: " + std::to_string(IShape::GetOutlineThickness()) + "\n";
    res += "Позиция начала: " + m_startPoint.ToString() + "\n";
    res += "Позиция конца: " + m_endPoint.ToString() + "\n";

    return res;
}

