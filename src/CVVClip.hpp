#pragma once

#include <vector>

#include "Semantic.h"

namespace XRender
{
    void ClipTriangleDetail(std::vector<VertexOutput>& out_verteies, const VertexOutput** triangle, const Vec4f* points)
    {
        for(uint32_t index = 0; index < 3; ++index)
        {
            out_verteies.emplace_back(*(triangle[index]));
        }
    }
}