#include "ShadowSetting.h"

bool XRender::ShadowSetting::enable_shadow = true;
float XRender::ShadowSetting::shadow_distance = 20.0f;
uint32_t XRender::ShadowSetting::width = 512;
uint32_t XRender::ShadowSetting::height = 512;
uint32_t XRender::ShadowSetting::shadow_strength = 1;
float XRender::ShadowSetting::const_bias = 0.06f;
float XRender::ShadowSetting::gradient_scale_bias = 5.f;
float XRender::ShadowSetting::gradient_diff_min = 0.002f;


const Vec2f& XRender::ShadowSetting::InvertSize()
{
    static Vec2f invert_size;
    invert_size.x = 1.0f / XRender::ShadowSetting::width;
    invert_size.y = 1.0f / XRender::ShadowSetting::height;
    return invert_size;
}