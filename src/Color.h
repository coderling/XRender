#pragma once
#include <stdint.h>

namespace XRender
{

    struct Color
    {
    public:
        Color() = default;
        Color(const float& r, const float& g, const float& b, const float& a);
        float r;
        float g;
        float b;
        float a;
    };

    Color operator*(const Color& lcolor, const float& v);
    Color operator*(const Color& lcolor, const Color& rcolor);
    Color operator+(const Color& lcolor, const Color& rcolor);

    struct Color32
    {
    public:
        Color32() = default;
        Color32(const uint8_t& r, const uint8_t& g, const uint8_t& b, const uint8_t& a);
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };

    namespace CColor
    {
        const Color Wihte = {1, 1, 1, 1};
        const Color BLACK = {0, 0, 0, 1};
        const Color RED = {1, 0, 0, 1};
        const Color GREEN = {0, 1, 0, 1};
        const Color BLUE = {0, 0, 1, 1};
    }

    Color32 ColorToColor32(const Color& color);
    Color Color32ToColor(const Color32& color);
}