//
// Created by xac1k on 5/7/26.
//

#include <iostream>
#include <ostream>
#include <SFML/Window/Keyboard.hpp>

#include "utils/Drawer/window/implementation/CWindow.h"
#include "utils/Drawer/window/implementation/Events.h"
#include "utils/Steihner/SteineResolver.h"

constexpr uint32_t mainColor = 0xFF653F;
constexpr uint32_t additionalColor = 0x00FF00;
constexpr uint32_t BLACK = 0;

constexpr uint32_t mainRadius = 10;
constexpr uint32_t additionalRadius = 5;

int main(int argc, char *argv[]) {
    std::vector<std::pair<size_t, CPoint>> terminals = {};
    size_t counter = -1;

    CWindow win;
    win.Clear();

    win.Subscribe<MouseClickEvent>([&](const MouseClickEvent& e){
        win.FillCircle({e.x, e.y}, mainRadius, mainColor);
        terminals.push_back({counter++, {e.x, e.y}});
    });

    win.Subscribe<KeyPressEvent>([&](const KeyPressEvent& e) {
        if (e.keyCode == sf::Keyboard::C) {
            win.Clear();
            terminals.clear();
        }
        else if (e.keyCode == sf::Keyboard::S) {
            auto graph = FindOptimalTree(terminals);

            win.Clear();
            for (const auto& edge : graph.edges) {
                auto findNode = [&](size_t id) -> const Node& {
                    for (const auto& n : graph.nodes)
                        if (n.id == id) return n;
                    throw std::runtime_error("not found");
                };
                const auto& from = findNode(edge.from).point;
                const auto& to   = findNode(edge.to).point;
                win.DrawLine(from, to, BLACK, 2);
            }

            for (const auto& node : graph.nodes) {
                if (node.type == NodeType::Terminal)
                    win.FillCircle(node.point, mainRadius, mainColor);
                else
                    win.FillCircle(node.point, additionalRadius, additionalColor);
            }

        }
    });

    win.Open();
}