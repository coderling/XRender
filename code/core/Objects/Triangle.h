/*
 * File: Triangle.h
 * File Created: Tuesday, 23rd October 2018 10:08:16 pm
 * Author: coderling (coderling@gmail.com)
 */

#pragma once

#include "code/core/basic/Mesh.h"
#include "code/core/primitive/Vertex.h"

class Triangle : public Mesh
{
public:

    Triangle(Vertex& a, Vertex& b, Vertex& c);
    
    inline Vertex* GetVerteies(){ return m_verteies; }

    inline const int* GetIndeies(int* count){ *count = 3; return m_indeies; }

private:
    
    Vertex m_verteies[3];
    static const int m_indeies[3];
};