//
// Created by xac1k on 5/7/26.
//

#include "./Steiner.h"

#include <algorithm>
#include <complex>
#include <variant>
#include <cmath>
#include <memory>
#include <vector>

#include "../../Drawer/shape/CCircle.h"

CTriangle Steiner::BuildEquilateralTriangle(const CPoint p1, const CPoint p2, Side s) {
    CTriangle t;
    t.SetVertex(1, p1);
    t.SetVertex(2, p2);

    const auto v = CVector(p2 - p1);
    const CPoint mid = (p1 + p2) / 2;

    double height = v.dist() * std::sqrt(3.0) / 2.0;
    CVector perp = {-v.y, v.x};
    perp /= perp.dist();

    double x3 = 0, y3 = 0;
    if (s == Side::Left) {
        x3 = mid.x + perp.x * height;
        y3 = mid.y + perp.y * height;
    } else if (s == Side::Right) {
        x3 = mid.x - perp.x * height;
        y3 = mid.y - perp.y * height;
    }
    t.SetVertex(3, {x3, y3});

    return t;
}

CPoint Steiner::FindCenterCircumscribedCircle(const CTriangle &t) {
    const auto p1 = t.GetVertex(1);
    const auto p2 = t.GetVertex(2);
    const auto p3 = t.GetVertex(3);

    const double x1 = p1.x, y1 = p1.y;
    const double x2 = p2.x, y2 = p2.y;
    const double x3 = p3.x, y3 = p3.y;

    const double d = 2.0 * (x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2));

    if (std::abs(d) < 1e-6) {
        throw std::runtime_error("Points are collinear, cannot find circumscribed circle");
    }

    const double x1_2 = x1*x1, y1_2 = y1*y1;
    const double x2_2 = x2*x2, y2_2 = y2*y2;
    const double x3_2 = x3*x3, y3_2 = y3*y3;

    const double ux = ((x1_2 + y1_2)*(y2 - y3) +
                       (x2_2 + y2_2)*(y3 - y1) +
                       (x3_2 + y3_2)*(y1 - y2)) / d;

    const double uy = ((x1_2 + y1_2)*(x3 - x2) +
                       (x2_2 + y2_2)*(x1 - x3) +
                       (x3_2 + y3_2)*(x2 - x1)) / d;

    return CPoint(ux, uy);
}
bool IsPointValidForLine(double tCoeff) {
    return tCoeff <= 1 && tCoeff >= 0;
}
CPoint RemapStartPointAlignVectorAndTInCPoint(const CLineSegment & line, double T, const CPoint& df ) {
    return CPoint(line.GetStartPoint().x + T * df.x, line.GetStartPoint().y + T * df.y);
}

constexpr int NO_POINTS_OF_OVERLAP = -1;
std::variant<int, CPoint, std::tuple<CPoint, CPoint>> FindOverlaps(const CLineSegment &line, const CCircle &circle) {
    const auto diffLine = line.GetEndPoint() - line.GetStartPoint();
    const auto diffCircle = line.GetStartPoint() - circle.GetPosition();

    const auto a = std::pow(diffLine.x, 2) + std::pow(diffLine.y, 2);
    const auto b = 2 * (diffCircle.x * diffLine.x + diffCircle.y * diffLine.y);
    const auto c = std::pow(diffCircle.x, 2) + std::pow(diffCircle.y, 2) - std::pow(circle.GetRadius(), 2);

    if (a == 0)
        throw std::invalid_argument("Error in LineSegment: start point and end point are equal.");

    const auto D = b * b - 4 * a * c;
    if (D == 0) {
        const auto t = -b / (2*a);
        if (IsPointValidForLine(t))
        return RemapStartPointAlignVectorAndTInCPoint(line, t, diffLine);
    }
    if (D > 0) {
        const auto t1 = (-b - std::sqrt(D)) / (2 * a);
        const auto t2 = (-b + std::sqrt(D)) / (2 * a);

        if (IsPointValidForLine(t1) && IsPointValidForLine(t2))
            return std::make_tuple(
                RemapStartPointAlignVectorAndTInCPoint(line, t1, diffLine),
                RemapStartPointAlignVectorAndTInCPoint(line, t2, diffLine)
            );
        if (IsPointValidForLine(t1))
            return RemapStartPointAlignVectorAndTInCPoint(line, t1, diffLine);
        if (IsPointValidForLine(t2))
            return RemapStartPointAlignVectorAndTInCPoint(line, t2, diffLine);
    }
    return NO_POINTS_OF_OVERLAP;
}
constexpr double EPSILON = 0.0001;
bool CompareWithEpsilon(const double x, const double y) {
    return std::abs(x - y) < EPSILON;
}
bool CompareWithEpsilon(const CPoint& p1, const CPoint& p2) {
    return CompareWithEpsilon(p1.x, p2.x)
    && CompareWithEpsilon(p1.y, p2.y);
}
bool IsPointValidForSteiner(const CPoint& p, const CLineSegment& l) {
    return !(CompareWithEpsilon(p, l.GetStartPoint()) || CompareWithEpsilon(p, l.GetEndPoint()));
}
std::variant<int, CPoint> Steiner::FindOverlapLineAndCircle(const CLineSegment& l, const CCircle& c) {
    std::variant<int, CPoint, std::tuple<CPoint, CPoint>> overlappingPoints;
    try {
        overlappingPoints = FindOverlaps(l, c);
    }
    catch (std::exception& e) {
        return NO_POINTS_OF_OVERLAP;
    }

    if (overlappingPoints.index() == 0)
        return NO_POINTS_OF_OVERLAP;
    if (overlappingPoints.index() == 1) {
        auto candidate = std::get<CPoint>(overlappingPoints);
        if (IsPointValidForSteiner(candidate, l))
            return candidate;
        return NO_POINTS_OF_OVERLAP;
    }
    if (overlappingPoints.index() == 2) {
        auto [p1, p2] = std::get<std::tuple<CPoint, CPoint>>(overlappingPoints);
        if (IsPointValidForSteiner(p1, l))
            return p1;
        if (IsPointValidForSteiner(p2, l))
            return p2;
        return NO_POINTS_OF_OVERLAP;
    }
    return NO_POINTS_OF_OVERLAP;
}

double ComputeOrderedAngleBetweenVectors(const CVector &v1, const CVector &v2) {
    const auto scalar = v1.x * v2.x + v1.y * v2.y;
    const auto det = v1.x * v2.y - v1.y * v2.x;
    return std::atan2(det, scalar) * 180 / M_PI;
}
std::tuple<CPoint, CPoint, CPoint> GetOrderedPoints(const Steiner::Point& sp) {
    const CPoint& S = sp.steinerPoint;

    auto angle = [&](const CPoint& p) {
        return std::atan2(p.y - S.y, p.x - S.x);
    };

    std::vector<CPoint> pts = { sp.p1, sp.p2, sp.p3 };
    std::sort(pts.begin(), pts.end(), [&](const CPoint& a, const CPoint& b) {
        return angle(a) < angle(b);
    });

    return { pts[0], pts[1], pts[2] };
}
int Sign(const double x) {
    return x < 0 ? -1 : 1;
}
bool Steiner::IsValidSteinerPoint(const Point& steinerPoint) {
    auto [p1, p2, p3] = GetOrderedPoints(steinerPoint);

    const auto v1 = CVector(p1 - steinerPoint.steinerPoint);
    const auto v2 = CVector(p2 - steinerPoint.steinerPoint);
    const auto v3 = CVector(p3 - steinerPoint.steinerPoint);

    const auto a12 = ComputeOrderedAngleBetweenVectors(v1, v2);
    const auto a23 = ComputeOrderedAngleBetweenVectors(v2, v3);
    const auto a31 = ComputeOrderedAngleBetweenVectors(v3, v1);

    return a12 > 0 && a23 > 0 && a31 > 0
        && a12 <= 120.0 + EPSILON
        && a23 <= 120.0 + EPSILON
        && a31 <= 120.0 + EPSILON;
}

std::optional<Steiner::Point>  Steiner::GetSteinerPoint(CPoint &p1, CPoint &p2, CPoint &p3, Side s) {
    const CTriangle t = Steiner::BuildEquilateralTriangle(p1, p2, s);
    const CPoint center = Steiner::FindCenterCircumscribedCircle(t);
    CCircle c;
    CLineSegment l;
    c.SetPosition(center).SetRadius(CVector(t.GetVertex(1) - center).dist());
    l.SetEndPoint(p3).SetStartPoint(t.GetVertex(3));

    const auto overlappingPoints = Steiner::FindOverlapLineAndCircle(l, c);
    if (overlappingPoints.index() == 1) {
        const auto overlapPoint = std::get<CPoint>(overlappingPoints);
        const auto isValid = Steiner::IsValidSteinerPoint({
            .steinerPoint = overlapPoint,
            .p1 = p1,
            .p2 = p2,
            .p3 = p3,
            .from = t.GetVertex(3),
        });
        if (isValid)
            return std::optional<Steiner::Point>({overlapPoint, p1, p2, p3, t.GetVertex(3)});
        throw AngleNotValidError();
    }
    throw OverlapNotExistError();
}
std::optional<Steiner::Point> Steiner::GetSteinerPoint(CPoint& p1, CPoint& p2, CPoint& p3) {
    try {
        const auto variant1 = GetSteinerPoint(p1, p2, p3, Side::Left);
        return variant1;
    }
    catch (const OverlapNotExistError& e) {
        try {
            const auto variant2 = GetSteinerPoint(p1, p2, p3, Side::Right);
            return variant2;
        }
        catch ([[maybe_unused]] const AngleNotValidError& e1) {
            throw;
        }
        catch ([[maybe_unused]] const OverlapNotExistError& e2) {
            throw;
        }
    }
}

std::optional<Steiner::Point> Steiner::GetSteinerPoint(std::shared_ptr<CPoint> p1, std::shared_ptr<CPoint> p2, std::shared_ptr<CPoint> p3) {
    return GetSteinerPoint(*p1.get(), *p2.get(), *p3.get());
}

std::optional<Steiner::Point> Steiner::GetSteinerPoint(CPoint &&p1, CPoint &&p2, CPoint &&p3) {
    return GetSteinerPoint(p1, p2, p3);
}
