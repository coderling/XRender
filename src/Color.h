#pragma once
#include <stdint.h>

namespace XRender
{

struct Color
{
public:
    float r;
    float g;
    float b;
    float a;
};

struct Color32
{
public:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

namespace CColor
{
    const Color Wihte = {0, 0, 0};
    const Color BLACK = {0, 0, 0};
    const Color RED = {1, 0, 0};
    const Color GREEN = {0, 1, 0};
    const Color BLUE = {0, 0, 1};
}
}