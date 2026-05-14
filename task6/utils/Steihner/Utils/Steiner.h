//
// Created by xac1k on 5/7/26.
//

#ifndef MAIN_STEINER_H
#define MAIN_STEINER_H
#include <set>
#include <variant>
#include <vector>

#include "../../Drawer/common/CPoint.h"
#include "../../Drawer/shape/CCircle.h"
#include "../../Drawer/shape/CLineSegment.h"
#include "../../Drawer/shape/CTriangle.h"

class Steiner {
public:
    struct Point {
        CPoint steinerPoint;
        CPoint& p1;
        CPoint& p2;
        CPoint& p3;
    };
    enum class Side{Right, Left};
    static std::optional<Point> GetSteinerPoint(CPoint &p1, CPoint &p2, CPoint &p3);

private:
    static std::optional<Point> GetSteinerPoint(CPoint& p1, CPoint& p2, CPoint& p3, Side s);
    static CTriangle BuildEquilateralTriangle(CPoint p1, CPoint p2, Side s);
    static CPoint FindCenterCircumscribedCircle(const CTriangle &t);
    static std::variant<int, CPoint> FindOverlapLineAndCircle(const CLineSegment&, const CCircle&);
    static bool IsValidSteinerPoint(const Point&);
};


#endif //MAIN_STEINER_H