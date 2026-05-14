//
// Created by xac1k on 4/5/26.
//

#ifndef TESTS_CCIRCLE_H
#define TESTS_CCIRCLE_H
#include "../common/CPoint.h"
#include "ISolidShape.h"


class CCircle : public ISolidShape {
public:
    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;

    CCircle& SetPosition(const CPoint& point);
    CCircle& SetRadius(double radius);
    CPoint GetPosition() const;
    double GetRadius() const;

private:
    CPoint m_position = {0, 0};
    double m_radius = 0;

    void ClearCache() const;
};


#endif //TESTS_CCIRCLE_H