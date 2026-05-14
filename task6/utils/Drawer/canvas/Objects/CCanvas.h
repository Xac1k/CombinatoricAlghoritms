//
// Created by xac1k on 4/9/26.
//

#ifndef TESTS_CCANVAS_H
#define TESTS_CCANVAS_H

#include "SFML/Graphics.hpp"
#include "../Interface/ICanvas.h"
#include "../../shape/CTriangle.h"

class CCanvas : public ICanvas {
public:
    CCanvas();
    CCanvas(uint16_t width, uint16_t height);
    ~CCanvas() override;

    void DrawCircle(CPoint center, double radius, uint32_t lineColor, uint32_t thickness) override;
    void DrawLine(CPoint start, CPoint end, uint32_t lineColor, uint32_t thickness) override;
    void FillCircle(CPoint center, double radius, uint32_t fillColor) override;
    void FillPolygon(std::vector<CPoint> points, uint32_t fillColor) override;

    void Open() override;
    void Clear() override;
private:
    static constexpr uint16_t DEFAULT_WIDTH = 800;
    static constexpr uint16_t DEFAULT_HEIGHT = 600;

    sf::RenderWindow m_window;
};

#endif //TESTS_CCANVAS_H