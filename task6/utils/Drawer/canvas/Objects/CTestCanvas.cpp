//
// Created by xac1k on 4/9/26.
//

#include "./CTestCanvas.h"
#include "iostream"

CTestCanvas::CTestCanvas(): CTestCanvas(DEFAULT_WIDTH, DEFAULT_HEIGHT) {
    std::cout << "CTestCanvas()->CTestCanvas(width, height)" << " | ";
}

CTestCanvas::CTestCanvas(const uint16_t width, const uint16_t height) {
    std::cout << "exec CTestCanvas(width, height): "<< width << " " << height << " | ";
}

CTestCanvas::~CTestCanvas() {
    std::cout << "~CTestCanvas()" << " | ";
}

void CTestCanvas::DrawLine(const CPoint start, const CPoint end, const uint32_t lineColor, const uint32_t thickness) {
    std::cout << "add first point to vertex array: " << start.ToString() << " | ";
    std::cout << "add second point to vertex array: " << end.ToString() << " | ";
    std::cout << "set lineColor: " << lineColor << " | ";
    std::cout << "set thickness: " << thickness << " | ";

    std::cout << "draw line" << " | ";
}

void CTestCanvas::FillPolygon(std::vector<CPoint> points, uint32_t fillColor) {
    if (points.size() < 3)
        throw std::invalid_argument("points must be at least 3");

    std::cout << "set count of points: " << points.size() << " | ";

    int pointID = 0;
    for (auto point : points) {
        std::cout << "set point " << pointID << " how " << point.ToString() << " | ";
        ++pointID;
    }

    std::cout << "set fillColor: " << fillColor << " | ";
    std::cout << "draw convex | ";
}

void CTestCanvas::FillCircle(const CPoint center, const double radius, const uint32_t fillColor) {
    std::cout << "set radius: " << radius << " | ";
    std::cout << "set position: " << center.ToString() << " | ";
    std::cout << "set fillColor: " << fillColor << " | ";

    std::cout << "draw filled circle" << " | ";
}

void CTestCanvas::DrawCircle(const CPoint center, const double radius, const uint32_t lineColor, const uint32_t thickness) {
    std::cout << "set radius: " << radius << " | ";
    std::cout << "set position: " << center.ToString() << " | ";
    std::cout << "set outlineColor: " << lineColor << " | ";
    std::cout << "set thickness: " << thickness << " | ";

    std::cout << "draw outlined circle" << " | ";
}

void CTestCanvas::Open() {
    std::cout << "show canvas" << " | ";
}

void CTestCanvas::Clear() {
    std::cout << "clear canvas" << " | ";
}
