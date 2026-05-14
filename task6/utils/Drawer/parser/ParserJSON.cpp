//
// Created by xac1k on 4/10/26.
//

#include <regex>

#include "ParserJSON.h"

#include <variant>

#include "../drawable/Objects/CDCircle.h"
#include "../drawable/Objects/CDLineSegment.h"
#include "../drawable/Objects/CDRectangle.h"
#include "../drawable/Objects/CDTriangle.h"

/* Circle: {
 *   position: 32 px, 32 px;
 *   radius: 32 px;
 *   outlineColor: 34343;
 *   outlineThickness: 32 px;
 *   fillColor: 32;
 * }
 */

/* Line: {
 *   outlineColor: 34343;
 *   outlineThickness: 32 px;
 *   start: 32 px, 32 px;
 *   end: 32 px, 32 px;
 * }
 */

/* Rectangle: {
 *   outlineColor: 34343;
 *   outlineThickness: 32 px;
 *   fillColor: 34343;
 *   position: 32 px, 32 px;
 *   size: 32 px, 32 px;
 * }
 */

/* Triangle: {
 *   outlineColor: 34343;
 *   outlineThickness: 32 px;
 *   fillColor: 34343;
 *   Vertex1: 32 px, 32 px;
 *   Vertex2: 32 px, 32 px;
 *   Vertex3: 32 px, 32 px;
 * }
 */

const std::regex patternObjectJSON(R"(\s*(\w+):\s*\{([\s\d\w:,;]*)\})");
const std::regex PatternAttribute(R"(\s*([\d\w\s]+):\s*([\d\w\s,]*);)");
const std::regex PatternVectorPX(R"(\s*(\d+)\s*px\s*,\s*(\d+)\s*px\s*)");
const std::regex PatternPointPX(R"(\s*(\d+)\s*px\s*)");
const std::regex PatternPoint(R"(\s*(\d+)\s*)");

using PossibleAttributeTypes = std::variant<uint32_t, double, CPoint>;
using AttributesType = std::map<std::string, PossibleAttributeTypes>;

using namespace std::literals;

enum class ShapeType {Triangle, Rectangle, Circle, LineSegment, Unknown};

ShapeType GetShapeType(const std::string& textType) {
    if (textType == "Triangle")
        return ShapeType::Triangle;
    else if (textType == "Rectangle")
        return ShapeType::Rectangle;
    else if (textType == "Circle")
        return ShapeType::Circle;
    else if (textType == "Line")
        return ShapeType::LineSegment;
    else
        return ShapeType::Unknown;
}

PossibleAttributeTypes ParseAttributeJSON(const std::string& json) {
    PossibleAttributeTypes res;

    if (std::smatch match; std::regex_match(json, match, PatternVectorPX)) {
        res = CPoint(std::stod(match[1].str()), std::stod(match[2].str()));
    }
    else if (std::regex_match(json, match, PatternPointPX)) {
        res = std::stod(match[1].str());
    }
    else if (std::regex_match(json, match, PatternPoint)) {
        res = static_cast<uint32_t>(std::stol(match[1].str()));
    }
    else {
        throw std::runtime_error("Failed to parse attribute: " + json);
    }

    return res;
}

AttributesType ParseBodyJSON(const std::string& json) {
    AttributesType res;
    const auto begin = std::sregex_iterator(json.begin(), json.end(), PatternAttribute);
    const auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it) {
        const std::smatch& match = *it;
        res.insert(std::make_pair(match[1].str(), ParseAttributeJSON(match[2].str())));
    }

    return res;
}

struct JSONObject {
    ShapeType type;
    AttributesType attributes;
};

std::vector<JSONObject> ParseJSON(const std::string& json) {
    std::vector<JSONObject> result;

    const auto begin = std::sregex_iterator(json.begin(), json.end(), patternObjectJSON);
    const auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it) {
        const std::smatch& match = *it;

        JSONObject obj = {
            .type=GetShapeType(match[1].str()),
            .attributes=ParseBodyJSON(match[2].str())
        };

        result.push_back(obj);
    }
    return result;
}

template <typename AttributeType>
AttributeType GetAttribute(const AttributesType& attribute, const std::string& attributeName) {
    const auto it = attribute.find(attributeName);
    if (it == attribute.end())
        throw std::runtime_error("Attribute " + attributeName + " does not exist.");

    auto res = std::get<AttributeType>(it->second);
    return res;
}

std::unique_ptr<ICanvasDrawable> ConvertObjectToDrawable(const JSONObject& obj) {
    if (obj.type == ShapeType::Triangle) {
        auto tri = std::make_unique<CDTriangle>();
        tri->SetVertex(1, GetAttribute<CPoint>(obj.attributes, "Vertex1"))
            .SetVertex(2, GetAttribute<CPoint>(obj.attributes, "Vertex2"))
            .SetVertex(3, GetAttribute<CPoint>(obj.attributes, "Vertex3"))
            .SetFillColor(GetAttribute<uint32_t>(obj.attributes, "fillColor"))
            .SetOutlineColor(GetAttribute<uint32_t>(obj.attributes, "outlineColor"))
            .SetOutlineThickness(GetAttribute<uint32_t>(obj.attributes, "outlineThickness"));
        return tri;
    }
    else if (obj.type == ShapeType::Rectangle) {
        auto rect = std::make_unique<CDRectangle>();
        const auto [x, y] = GetAttribute<CPoint>(obj.attributes, "size");
        rect->SetPosition(GetAttribute<CPoint>(obj.attributes, "position"))
            .SetWidth(x)
            .SetHeight(y)
            .SetFillColor(GetAttribute<uint32_t>(obj.attributes, "fillColor"))
            .SetOutlineColor(GetAttribute<uint32_t>(obj.attributes, "outlineColor"))
            .SetOutlineThickness(GetAttribute<uint32_t>(obj.attributes, "outlineThickness"));
        return rect;
    }
    else if (obj.type == ShapeType::Circle) {
        auto circle = std::make_unique<CDCircle>();
        circle->SetPosition(GetAttribute<CPoint>(obj.attributes, "position"))
            .SetRadius(GetAttribute<double>(obj.attributes, "radius"))
            .SetFillColor(GetAttribute<uint32_t>(obj.attributes, "fillColor"))
            .SetOutlineColor(GetAttribute<uint32_t>(obj.attributes, "outlineColor"))
            .SetOutlineThickness(GetAttribute<uint32_t>(obj.attributes, "outlineThickness"));
        return circle;
    }
    else if (obj.type == ShapeType::LineSegment) {
        auto line = std::make_unique<CDLineSegment>();
        line->SetStartPoint(GetAttribute<CPoint>(obj.attributes, "start"))
            .SetEndPoint(GetAttribute<CPoint>(obj.attributes, "end"))
            .SetOutlineColor(GetAttribute<uint32_t>(obj.attributes, "outlineColor"))
            .SetOutlineThickness(GetAttribute<uint32_t>(obj.attributes, "outlineThickness"));
        return line;
    }
    else
        throw std::runtime_error("Unknown shape type. There is an error in signature of file.");

}

std::vector<std::unique_ptr<ICanvasDrawable>> ParserJSON::Parse(const std::string &line) {
    std::vector<std::unique_ptr<ICanvasDrawable>> result;

    for (const auto objects = ParseJSON(line); const auto& object : objects)
        result.push_back(ConvertObjectToDrawable(object));

    return result;
}