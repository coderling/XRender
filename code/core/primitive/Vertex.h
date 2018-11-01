#pragma once
//顶点数据
#include <SDL.h>

#include "../math/Vector3.h"

class Color
{
public:
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;

    Color(){ r = g = b = 0, a = 255;}
    Color(Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a)
    {
        r = _r, g = _g, b = _b, a = _a;
    }
    Color(const Color& col)
    {
        r = col.r, g = col.g, b = col.b, a = col.a;
    }
};

class Vertex
{
public:
    Vertex(){}
    Vertex(Vector3& _pos, Color& _col)
    {
        pos.x = _pos.x; pos.y = _pos.y; pos.z = _pos.z;
        color.r = _col.r; color.g = _col.g; color.b = _col.b; color.a = _col.a;
    }
    Vector3 pos;
    Color color;
};