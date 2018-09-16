#pragma once

#include "Vertex.h"

class Triangle
{
public:
    Triangle(){}
    Vertex vertexics[3];
    //default index 0, 1, 2
    static Uint32 indexes[3];
};


Uint32 Triangle::indexes[3] = {0, 1, 2};
