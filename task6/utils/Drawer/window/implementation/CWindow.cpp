//
// Created by xac1k on 5/7/26.
//

#include "./CWindow.h"
#include "./Events.h"
#include <SFML/Graphics.hpp>

CWindow::CWindow(): CWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT) {}

CWindow::CWindow(uint16_t width, uint16_t height): m_window(sf::VideoMode(width, height), "CWindow", sf::Style::Default) {
    m_window.clear(sf::Color::White);
}

CWindow::~CWindow() {
    if (m_window.isOpen()) {
        m_window.close();
    }
}

void CWindow::DrawLine(const CPoint start, const CPoint end, const uint32_t lineColor, const uint32_t thickness) {
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

void CWindow::FillPolygon(const std::vector<CPoint> points, const uint32_t fillColor) {
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

void CWindow::FillCircle(const CPoint center, const double radius, const uint32_t fillColor) {
    sf::CircleShape circle;
    circle.setRadius(static_cast<float>(radius));
    circle.setOrigin(static_cast<float>(radius), static_cast<float>(radius));
    circle.setPosition(static_cast<float>(center.x), static_cast<float>(center.y));
    circle.setFillColor(sf::Color (
        (fillColor >> 16) & 0xFF,
        (fillColor >> 8) & 0xFF,
        fillColor & 0xFF,
        255
    ));

    m_window.draw(circle);
    m_window.display();
}

void CWindow::DrawCircle(const CPoint center, const double radius, const uint32_t lineColor, const uint32_t thickness) {
    sf::CircleShape circle;
    circle.setRadius(static_cast<float>(radius));
    circle.setOrigin(static_cast<float>(radius), static_cast<float>(radius));
    circle.setPosition(static_cast<float>(center.x), static_cast<float>(center.y));
    circle.setOutlineThickness(static_cast<float>(thickness));
    circle.setOutlineColor(sf::Color (
        (lineColor >> 16) & 0xFF,
        (lineColor >> 8) & 0xFF,
        lineColor & 0xFF,
        255
    ));

    m_window.draw(circle);
}

void CWindow::Open() {
    while (m_window.isOpen()) {
        sf::Event event{};

        while(m_window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                m_window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                Dispatch(KeyPressEvent(
                    event.key.code,
                    event.key.alt,
                    event.key.control,
                    event.key.shift
                ));
            }
            if (event.type == sf::Event::Resized) {
                Dispatch(WindowResizeEvent(
                    static_cast<int>(event.size.width),
                    static_cast<int>(event.size.height)
                ));
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                MouseClickEvent::Button btn;
                switch (event.mouseButton.button) {
                    case sf::Mouse::Left:
                        btn = MouseClickEvent::Button::Left;
                        break;
                    case sf::Mouse::Right:
                        btn = MouseClickEvent::Button::Right;
                        break;
                    case sf::Mouse::Middle:
                        btn = MouseClickEvent::Button::Middle;
                        break;
                    default:
                        continue;
                }
                Dispatch(MouseClickEvent(
                    btn,
                    static_cast<float>(event.mouseButton.x),
                    static_cast<float>(event.mouseButton.y)
                ));
            }
            if (event.type == sf::Event::MouseMoved) {
                Dispatch(MouseMoveEvent(
                    static_cast<float>(event.mouseMove.x),
                    static_cast<float>(event.mouseMove.y)
                ));
            }
        }

        m_window.display();
    }
}

void CWindow::Clear() {
    m_window.clear(sf::Color::White);
}

CPoint CWindow::GetSize() {
    return {static_cast<double>(m_window.getSize().x), static_cast<double>(m_window.getSize().y)};
}
