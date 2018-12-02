/*
 * Filename: /Users/coderling/Documents/DEVLab/XRender/code/core/Object/Cube.cpp
 * Path: /Users/coderling/Documents/DEVLab/XRender/code/core/Object
 * Created Date: Wednesday, September 12th 2018, 12:05:50 am
 * Author: coderling
 * 立方体实现 
 * Copyright (c) 2018 Your Company
 */

#include "Cube.h"

void Cube::InitVertexData()
{
    float hl = m_length / 2;
    float hw = m_width / 2;
    float hh = m_height / 2;

    m_verteies[0].pos.x = m_verteies[1].pos.x = m_verteies[2].pos.x = m_verteies[3].pos.x = -hw;
    m_verteies[4].pos.x = m_verteies[5].pos.x = m_verteies[6].pos.x = m_verteies[7].pos.x = hw;
    
    m_verteies[0].pos.y = m_verteies[4].pos.y = m_verteies[5].pos.y = m_verteies[1].pos.y = -hh;
    m_verteies[3].pos.y = m_verteies[7].pos.y = m_verteies[2].pos.y = m_verteies[6].pos.y = hh;
    
    m_verteies[0].pos.z = m_verteies[4].pos.z = m_verteies[3].pos.z = m_verteies[7].pos.z = -hl;
    m_verteies[1].pos.z = m_verteies[5].pos.z = m_verteies[2].pos.z = m_verteies[6].pos.z = hl;

    //uv
    m_verteies[0].uv.u = 0, m_verteies[0].uv.v = 0;
    m_verteies[1].uv.u = 0, m_verteies[1].uv.v = 1;
    m_verteies[2].uv.u = 1, m_verteies[2].uv.v = 1;
    m_verteies[3].uv.u = 1, m_verteies[3].uv.v = 0;

    m_verteies[4].uv.u = 0, m_verteies[4].uv.v = 0;
    m_verteies[5].uv.u = 0, m_verteies[5].uv.v = 1;
    m_verteies[6].uv.u = 1, m_verteies[6].uv.v = 1;
    m_verteies[7].uv.u = 1, m_verteies[7].uv.v = 0;

    m_verteies[0].color = Color(0, 0, 0, 255);
    m_verteies[1].color = Color(255, 0, 0, 255);
    m_verteies[2].color = Color(255, 255, 0, 255);
    m_verteies[3].color = Color(255, 255, 255, 255);
    m_verteies[4].color = Color(0, 255, 0, 255);
    m_verteies[5].color = Color(0, 255, 255, 255);
    m_verteies[6].color = Color(0, 0, 255, 255);
    m_verteies[7].color = Color(255, 0, 255, 255);
}

const int Cube::m_indeies[36] = {
    0, 1, 2,
    2, 3, 0,
    
    0, 1, 4,
    1, 5, 4,
    
    4, 5, 7,
    5, 6, 7,
    
    7, 3, 6,
    6, 3, 2,

    1, 2, 6,
    6, 5, 1,
 
    0, 3, 7,
    7, 4, 0
};