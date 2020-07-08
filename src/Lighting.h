#pragma once

#include <geometry.h>

#include "Color.h"

namespace XRender::Lighting 
{
    struct LightData 
    {
        float range;
        float intensity;
        Vec4f world_pos;
        Color color;
    };

    class Light final
    {
    public:
        LightData data;
    };
    
    const uint32_t max_light_num = 4;
    const LightData null_light{0, 0, {0, 0, 0, 0}, {0.5f, 0.5f, 0.5f, 1.f}};
}