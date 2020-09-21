#pragma once

#include "../src/Shader.h"
#include "../src/Semantic.h"
#include "../src/GraphicsGlobalData.h"
#include "../thirdParty/include/geometry.h"

inline float Linear01Depth(const float &depth) 
{
 float v = 1.0f / (XRender::GraphicsGlobalData::zbuffer_args.x * depth + XRender::GraphicsGlobalData::zbuffer_args.y);
    if (depth != 1)
        return v;
    return v;
}

    