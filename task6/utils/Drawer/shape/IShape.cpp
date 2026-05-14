//
// Created by xac1k on 4/4/26.
//

#include "./IShape.h"

IShape& IShape::SetOutlineColor(uint32_t color) {
    m_outlineColor = color;
    return *this;
}

IShape& IShape::SetOutlineThickness(uint32_t thickness) {
    m_outlineThickness = thickness;
    return *this;
}

uint32_t IShape::GetOutlineColor() const {
    return m_outlineColor;
}

uint32_t IShape::GetOutlineThickness() const {
    return m_outlineThickness;
}
