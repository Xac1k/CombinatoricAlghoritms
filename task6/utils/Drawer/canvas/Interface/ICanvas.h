//
// Created by xac1k on 4/8/26.
//

#ifndef TESTS_ICANVAS_H
#define TESTS_ICANVAS_H
#include <cstdint>
#include <vector>

#include "../../common/CPoint.h"

class ICanvas {
public:
    virtual ~ICanvas() = default;
    virtual void DrawLine(CPoint start, CPoint end, uint32_t lineColor, uint32_t thickness)=0;
    virtual void FillPolygon(std::vector<CPoint> points, uint32_t fillColor)=0;
    virtual void DrawCircle(CPoint center, double radius, uint32_t lineColor, uint32_t thickness)=0;
    virtual void FillCircle(CPoint center, double radius, uint32_t fillColor)=0;
    virtual void Open()=0;
    virtual void Clear()=0;
    virtual CPoint GetSize()=0;
};

#endif //TESTS_ICANVAS_H