//
// Created by xac1k on 4/9/26.
//

#include "./CCanvas.h"

CCanvas::CCanvas(): CCanvas(DEFAULT_WIDTH, DEFAULT_HEIGHT) {}

CCanvas::CCanvas(uint16_t width, uint16_t height): m_window(sf::VideoMode(width, height), "CCanvas", sf::Style::Default) {
    m_window.clear(sf::Color::White);
}

CCanvas::~CCanvas() {
    if (m_window.isOpen()) {
        m_window.close();
    }
}

void CCanvas::DrawLine(const CPoint start, const CPoint end, const uint32_t lineColor, const uint32_t thickness) {
    CVector dir = end - start;
    dir =  {dir.x / dir.dist(), dir.y / dir.dist()};
    sf::Vector2f perpendicular({static_cast<float>(-dir.y), static_cast<float>(dir.x)});

    sf::Vector2f startVect = {static_cast<float>(start.x), static_cast<float>(start.y)};
    sf::Vector2f endVect = {static_cast<float>(end.x), static_cast<float>(end.y)};
    sf::Vector2f offset = perpendicular * (static_cast<float>(thickness) / 2.0f);

    sf::VertexArray vertices(sf::Quads, 4);
    vertices[0].position = startVect - offset;
    vertices[1].position = startVect + offset;
    vertices[2].position = endVect + offset;
    vertices[3].position = endVect - offset;

    for (int i = 0; i < 4; i++) {
        vertices[i].color = sf::Color(sf::Color (
        (lineColor >> 16) & 0xFF,
        (lineColor >> 8) & 0xFF,
        lineColor & 0xFF,
        255
    ));
    }

    m_window.draw(vertices);
}

void CCanvas::FillPolygon(const std::vector<CPoint> points, const uint32_t fillColor) {
    if (points.size() < 3)
        throw std::invalid_argument("points must be at least 3");

    sf::ConvexShape convex;
    convex.setPointCount(points.size());

    int pointID = 0;
    for (auto point : points) {
        convex.setPoint(pointID, sf::Vector2f(static_cast<float>(point.x), static_cast<float>(point.y)));
        ++pointID;
    }

    convex.setFillColor(sf::Color (
        (fillColor >> 16) & 0xFF,
        (fillColor >> 8) & 0xFF,
        fillColor & 0xFF,
        255
    ));
    m_window.draw(convex);
}

void CCanvas::FillCircle(const CPoint center, const double radius, const uint32_t fillColor) {
    sf::CircleShape circle;
    circle.setRadius(static_cast<float>(radius));
    circle.setPosition(static_cast<float>(center.x - radius/2), static_cast<float>(center.y - radius/2));
    circle.setFillColor(sf::Color (
        (fillColor >> 16) & 0xFF,
        (fillColor >> 8) & 0xFF,
        fillColor & 0xFF,
        255
    ));

    m_window.draw(circle);
    m_window.display();
}

void CCanvas::DrawCircle(const CPoint center, const double radius, const uint32_t lineColor, const uint32_t thickness) {
    sf::CircleShape circle;
    circle.setRadius(static_cast<float>(radius));
    circle.setPosition(static_cast<float>(center.x - radius/2), static_cast<float>(center.y - radius/2));
    circle.setOutlineThickness(static_cast<float>(thickness));
    circle.setOutlineColor(sf::Color (
        (lineColor >> 16) & 0xFF,
        (lineColor >> 8) & 0xFF,
        lineColor & 0xFF,
        255
    ));

    m_window.draw(circle);
}

void CCanvas::Open() {
    m_window.display();

    while (m_window.isOpen()) {
        sf::Event event;

        while(m_window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                m_window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                event.mouseButton.button;

            }
        }
    }
}

void CCanvas::Clear() {
    m_window.clear();
}
