//
// Created by xac1k on 4/9/26.
//

#include "CDCircle.h"

void CDCircle::Draw(ICanvas &canvas) const {
    canvas.DrawCircle(GetPosition(), GetRadius(), GetOutlineColor(), GetOutlineThickness());
    canvas.FillCircle(GetPosition(), GetRadius(), GetFillColor());
}
