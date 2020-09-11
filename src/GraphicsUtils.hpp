#pragma once
#include "GraphicsGlobalData.h"

namespace XRender
{
    inline float Linear01Depth(const float &depth) 
    {
	    float v = 1.0f / (GraphicsGlobalData::zbuffer_args.x * depth + GraphicsGlobalData::zbuffer_args.y);
        if (depth != 1)
            return v;
        return v;
    }
}
