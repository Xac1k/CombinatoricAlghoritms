//
// Created by xac1k on 5/7/26.
//

#ifndef MAIN_STEINER_H
#define MAIN_STEINER_H
#include <memory>
#include <variant>

#include "../../Drawer/common/CPoint.h"
#include "../../Drawer/shape/CCircle.h"
#include "../../Drawer/shape/CLineSegment.h"
#include "../../Drawer/shape/CTriangle.h"
class OverlapNotExistError : public std::invalid_argument {
public:
    OverlapNotExistError() : std::invalid_argument("No overlaps exist") {};
};
class AngleNotValidError : public std::invalid_argument {
public:
    AngleNotValidError() : std::invalid_argument("Steiner Point not valid") {};
};

class Steiner {
public:
    struct Point {
        CPoint steinerPoint;
        CPoint p1;
        CPoint p2;
        CPoint p3;
        CPoint from; // точка с помощью которой строится точка штейнера, третья точка на треугольнике
    };
    enum class Side{Right, Left};
    static std::optional<Point> GetSteinerPoint(CPoint &p1, CPoint &p2, CPoint &p3);
    static std::optional<Point> GetSteinerPoint(CPoint &&p1, CPoint &&p2, CPoint &&p3);
    static std::optional<Point> GetSteinerPoint(std::shared_ptr<CPoint> p1, std::shared_ptr<CPoint> p2, std::shared_ptr<CPoint> p3);

private:
    static std::optional<Point> GetSteinerPoint(CPoint& p1, CPoint& p2, CPoint& p3, Side s);
    static CTriangle BuildEquilateralTriangle(CPoint p1, CPoint p2, Side s);
    static CPoint FindCenterCircumscribedCircle(const CTriangle &t);
    static std::variant<int, CPoint> FindOverlapLineAndCircle(const CLineSegment&, const CCircle&);
    static bool IsValidSteinerPoint(const Point&);
};


#endif //MAIN_STEINER_H