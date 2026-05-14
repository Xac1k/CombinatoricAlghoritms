//
// Created by xac1k on 4/9/26.
//

#include "CDLineSegment.h"

void CDLineSegment::Draw(ICanvas &canvas) const {
    canvas.DrawLine(GetStartPoint(), GetEndPoint(), GetOutlineColor(), GetOutlineThickness());
}
