//
// Created by xac1k on 4/4/26.
//

#ifndef TESTS_CPOINT_H
#define TESTS_CPOINT_H
#include <string>

struct CPoint {
    double x, y;
    bool operator==(const CPoint &other) const;
    CPoint operator+(const CPoint &other) const;
    CPoint operator-(const CPoint &other) const;
    CPoint operator/(double) const;
    std::string ToString() const;
};

struct CVector {
    double x, y;

    CVector(double x, double y);
    CVector(CPoint p);
    CVector& operator=(const CVector& other);
    ~CVector()=default;
    bool operator==(const CVector &other) const;
    CVector operator+(const CVector &other) const;
    CVector operator-(const CVector &other) const;
    CVector operator/(double) const;
    CVector& operator/=(double);
    CPoint toPoint() const;
    [[nodiscard]] double dist() const;
};

#endif //TESTS_CPOINT_H