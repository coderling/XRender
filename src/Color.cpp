#include <cmath>

#include "Color.h"

XRender::Color::Color(const float& r, const float& g, const float& b, const float& a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

XRender::Color32::Color32(const uint8_t& r, const uint8_t& g, const uint8_t& b, const uint8_t& a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

XRender::Color XRender::operator*(const XRender::Color& lcolor, const float& v)
{
    XRender::Color col;
    col.a = lcolor.a * v;
    col.r = lcolor.r * v;
    col.g = lcolor.g * v;
    col.b = lcolor.b * v;
    return col;
}

XRender::Color XRender::operator*(const XRender::Color& lcolor, const XRender::Color& rcolor)
{
    XRender::Color col;
    col.a = lcolor.a * rcolor.a;
    col.r = lcolor.r * rcolor.r;
    col.g = lcolor.g * rcolor.g;
    col.b = lcolor.b * rcolor.b;
    return col;
}

XRender::Color XRender::operator+(const XRender::Color& lcolor, const XRender::Color& rcolor)
{
    XRender::Color col;
    col.r = lcolor.r + rcolor.r;
    col.g = lcolor.g + rcolor.g;
    col.b = lcolor.b + rcolor.b;
    col.a = lcolor.a + rcolor.a;
    return col;
}

XRender::Color32 XRender::ColorToColor32(const XRender::Color &color)
{
    XRender::Color32 col;
    col.r = static_cast<uint8_t>(std::round(color.r * 255));
    col.g = static_cast<uint8_t>(std::round(color.g * 255));
    col.b = static_cast<uint8_t>(std::round(color.b * 255));
    col.a = static_cast<uint8_t>(std::round(color.a * 255));

    return col;
}

XRender::Color XRender::Color32ToColor(const XRender::Color32 &color)
{
    XRender::Color col;
    col.r = color.r * 1.f / 255;
    col.g = color.g * 1.f / 255;
    col.b = color.b * 1.f / 255;
    col.a = color.a * 1.f / 255;

    return col;
}