//
// Created by xac1k on 4/5/26.
//

#ifndef TESTS_CRECTANGLE_H
#define TESTS_CRECTANGLE_H

#include "../common/CPoint.h"
#include "ISolidShape.h"

class CRectangle : public ISolidShape {
public:
    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;

    CRectangle& SetPosition(const CPoint& point);
    CRectangle& SetWidth(double width);
    CRectangle& SetHeight(double height);
    CPoint GetPosition() const;
    double GetRadius() const;
    double GetHeight() const;
    double GetWidth() const;

private:
    CPoint m_position = {0, 0};
    CPoint m_size = {0, 0};

    void ClearCache() const;
};


#endif //TESTS_CRECTANGLE_H