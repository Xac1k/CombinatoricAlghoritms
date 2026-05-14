//
// Created by xac1k on 5/7/26.
//

#ifndef MAIN_CWINDOW_H
#define MAIN_CWINDOW_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Interface/IWindow.h"

class CWindow : public IWindow {
public:
    CWindow();
    CWindow(uint16_t width, uint16_t height);
    ~CWindow() override;

    void DrawCircle(CPoint center, double radius, uint32_t lineColor, uint32_t thickness) override;
    void DrawLine(CPoint start, CPoint end, uint32_t lineColor, uint32_t thickness) override;
    void FillCircle(CPoint center, double radius, uint32_t fillColor) override;
    void FillPolygon(std::vector<CPoint> points, uint32_t fillColor) override;
    void Open() override;
    void Clear() override;
    CPoint GetSize() override;
private:
    static constexpr uint16_t DEFAULT_WIDTH = 800;
    static constexpr uint16_t DEFAULT_HEIGHT = 600;

    sf::RenderWindow m_window;
};

#endif //MAIN_CWINDOW_H