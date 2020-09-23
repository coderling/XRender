#pragma once

#include <stdint.h>
#include <geometry.h>

namespace XRender
{
    class ShadowSetting final
    {
    public:
        static bool enable_shadow;
        static float shadow_distance;
        static uint32_t width;
        static uint32_t height;
        static uint32_t shadow_strength;
        static float const_bias;
        static float gradient_scale_bias;
        static float gradient_diff_min;
        static const Vec2f& InvertSize();
    };
}