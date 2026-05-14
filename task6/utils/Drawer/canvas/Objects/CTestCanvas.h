//
// Created by xac1k on 4/9/26.
//

#ifndef TESTS_CTESTCANVAS_H
#define TESTS_CTESTCANVAS_H

#include "../Interface/ICanvas.h"
#include "SFML/Graphics.hpp"

class CTestCanvas : public ICanvas {
public:
    CTestCanvas();
    CTestCanvas(uint16_t width, uint16_t height);
    ~CTestCanvas() override;

    void DrawCircle(CPoint center, double radius, uint32_t lineColor, uint32_t thickness) override;
    void DrawLine(CPoint start, CPoint end, uint32_t lineColor, uint32_t thickness) override;
    void FillCircle(CPoint center, double radius, uint32_t fillColor) override;
    void FillPolygon(std::vector<CPoint> points, uint32_t fillColor) override;
    void Open() override;
    void Clear() override;
private:
    static constexpr uint16_t DEFAULT_WIDTH = 800;
    static constexpr uint16_t DEFAULT_HEIGHT = 600;
};


#endif //TESTS_CTESTCANVAS_H