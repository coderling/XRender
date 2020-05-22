#pragma once
#include <geometry.h>

class Mesh
{
public:
    Vec3f* vertices;
    int* indeies;
    Vec3f* normals;
    Vec3f* colors;
    Vec2f* uv;
    Vec2f* uv2;
};