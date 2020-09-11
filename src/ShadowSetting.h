#pragma once

#include <stdint.h>

namespace XRender
{
    class ShadowSetting final
    {
    public:
        static bool enable_shadow;
        static float shadow_distance;
        static uint32_t width;
        static uint32_t height;
    };
}