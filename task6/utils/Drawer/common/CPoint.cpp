//
// Created by xac1k on 4/4/26.
//

#include "./CPoint.h"
#include <cmath>

CPoint CPoint::operator+(const CPoint &other) const {
    return CPoint(x + other.x, y + other.y);
}

CPoint CPoint::operator-(const CPoint &other) const {
    return CPoint(x - other.x, y - other.y);
}

bool CPoint::operator==(const CPoint &other) const {
    return x == other.x && y == other.y;
}

std::string CPoint::ToString() const {
    return std::to_string(x) + ", " + std::to_string(y);
}



CVector::CVector(CPoint p) {
    x = p.x;
    y = p.y;
}

CVector::CVector(double x, double y) {
    this->x = x;
    this->y = y;
}

CVector &CVector::operator=(const CVector &other) = default;

bool CVector::operator==(const CVector &other) const {
    return x == other.x && y == other.y;
}

CVector CVector::operator+(const CVector &other) const {
    return {x + other.x, y + other.y};
}

CVector CVector::operator-(const CVector &other) const {
    return {x - other.x, y - other.y};
}

double CVector::dist() const {
    return std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2));
}

CVector CVector::operator/(double delimiter) const {
    return CVector{x / delimiter, y / delimiter};
}

CPoint CPoint::operator/(double delimiter) const {
    return CPoint{x / delimiter, y / delimiter};
}

CPoint CVector::toPoint() const {
    return CPoint{x, y};
}

CVector &CVector::operator/=(double delimiter) {
    x /= delimiter;
    y /= delimiter;
    return *this;
}
