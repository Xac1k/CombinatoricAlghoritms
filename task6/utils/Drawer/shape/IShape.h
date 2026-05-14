//
// Created by xac1k on 4/4/26.
//

#ifndef LAB4_ISHAPE_H
#define LAB4_ISHAPE_H
#include <cstdint>
#include <optional>
#include <string>

class IShape {
public:
    virtual ~IShape() = default;

    virtual double GetArea() const=0;
    virtual double GetPerimeter() const=0;
    virtual std::string ToString() const=0;

    uint32_t GetOutlineColor() const;
    uint32_t GetOutlineThickness() const;

    IShape& SetOutlineColor(uint32_t color);
    IShape& SetOutlineThickness(uint32_t thickness);

protected:
    mutable std::optional<double> m_cachedArea;
    mutable std::optional<double> m_cachedPerimeter;
private:
    uint32_t m_outlineColor = 0;
    uint32_t m_outlineThickness = 0;
};


#endif //LAB4_ISHAPE_H