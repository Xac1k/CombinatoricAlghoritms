//
// Created by xac1k on 4/4/26.
//

#include "./ISolidShape.h"

#include <typeinfo>
#include <iostream>

uint32_t ISolidShape::GetFillColor() const {
    return m_FillColor;
}

ISolidShape& ISolidShape::SetFillColor(uint32_t color) {
    m_FillColor = color;
    return *this;
}
