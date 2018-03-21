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
};

class Vertex
{
public:
    Vector3 pos;
    Color color;
};