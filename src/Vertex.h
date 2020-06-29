#pragma once
#include "geometry.h"
#include "Color.h"

namespace XRender
{

struct Vertex
{
public:
    Vec3f pos;
    Vec3f normal;
    Color color;
    Vec2f uv;
    Vec2f uv2;
};

}
