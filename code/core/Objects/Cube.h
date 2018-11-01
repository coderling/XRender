/*
 * Filename: /Users/coderling/Documents/DEVLab/XRender/code/core/Object/Cube.h
 * Path: /Users/coderling/Documents/DEVLab/XRender/code/core/Object
 * Created Date: Tuesday, September 11th 2018, 11:49:29 pm
 * Author: coderling
 * 立方体 
 * Copyright (c) 2018 Your Company
 */


#pragma once

#include "code/core/basic/Object.h"
#include "code/core/primitive/Vertex.h"

class Cube : public Object
{
public:
    Cube(float l, float w, float h): m_length(l), m_width(w), m_height(h)
    {
        InitVertexData();
    }

    inline Vertex* GetVerteies(){ return m_verteies; }

    inline int GetIndeies(const int* pIndeies){  pIndeies = m_indeies; return 36; }

protected:
    float m_length;
    float m_width;
    float m_height;

    Vertex m_verteies[8];
    static const int m_indeies[36];

    void InitVertexData();
};
