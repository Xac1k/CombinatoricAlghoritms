//
// Created by xac1k on 4/5/26.
//

#ifndef TESTS_CLINESEGMENT_H
#define TESTS_CLINESEGMENT_H
#include "../common/CPoint.h"
#include "IShape.h"


class CLineSegment : public IShape {
public:
    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;

    CLineSegment& SetStartPoint(CPoint point);
    CLineSegment& SetEndPoint(CPoint point);

    CPoint GetStartPoint() const;
    CPoint GetEndPoint() const;
private:
    CPoint m_startPoint = {0, 0};
    CPoint m_endPoint = {0, 0};
};


#endif //TESTS_CLINESEGMENT_H