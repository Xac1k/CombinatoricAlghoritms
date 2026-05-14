//
// Created by xac1k on 4/9/26.
//

#include "CDRectangle.h"

void CDRectangle::Draw(ICanvas &canvas) const {
    CPoint leftUp = GetPosition();
    CPoint leftDown = GetPosition() + CPoint(0, GetHeight());
    CPoint rightUp = GetPosition() + CPoint(GetWidth(), 0);
    CPoint rightDown = GetPosition() + CPoint(GetWidth(), GetHeight());

    canvas.FillPolygon({leftUp, leftDown, rightDown, rightUp}, GetFillColor());

    canvas.DrawLine(leftUp, leftDown, GetOutlineColor(), GetOutlineThickness());
    canvas.DrawLine(leftDown, rightDown, GetOutlineColor(), GetOutlineThickness());
    canvas.DrawLine(rightDown, rightUp, GetOutlineColor(), GetOutlineThickness());
    canvas.DrawLine(rightUp, leftUp, GetOutlineColor(), GetOutlineThickness());
}
