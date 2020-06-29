#include "Color.h"

XRender::Color operator*(const XRender::Color& lcolor, const float& v)
{
    XRender::Color col;
    col.a = lcolor.a * v;
    col.r = lcolor.r * v;
    col.g = lcolor.g * v;
    col.b = lcolor.b * v;
}