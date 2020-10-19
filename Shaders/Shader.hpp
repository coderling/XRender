#pragma once
#include <algorithm>

#include "../src/Shader.h"
#include "../src/Semantic.h"
#include "../src/GraphicsGlobalData.h"
#include "../thirdParty/include/geometry.h"
#include "../src/GraphicsUtils.h"
#include "../src/ShadowSetting.h"

inline float Linear01Depth(const float &depth) 
{
 float v = 1.0f / (XRender::GraphicsGlobalData::zbuffer_args.x * depth + XRender::GraphicsGlobalData::zbuffer_args.y);
    if (depth != 1)
        return v;
    return v;
}

const float shadow_bias = 0.005;
float ComputeShadow(const Vec3f& world_pos, const Vec3f& normal)
{
    static Vec3f light_clip_pos;
    XRender::Math::TransformPoint(XRender::GraphicsGlobalData::matrix_shadow_light_vp, world_pos, light_clip_pos);
    // to [0, 1]
    light_clip_pos = (light_clip_pos + Vec3f_One) * 0.5f;
    if (light_clip_pos.x < 0 || light_clip_pos.y < 0)
        return 1;
    const auto& invert_size = XRender::ShadowSetting::InvertSize();
    
    const auto& current_depth = XRender::SampleShadowMap(light_clip_pos.x, light_clip_pos.y);
    Vec2f min_depth;
    min_depth.x = XRender::SampleShadowMap(light_clip_pos.x - invert_size.x, light_clip_pos.y);
    min_depth.y = XRender::SampleShadowMap(light_clip_pos.x, light_clip_pos.y - invert_size.y);
    Vec2f max_depth;
    max_depth.x = XRender::SampleShadowMap(light_clip_pos.x + invert_size.x, light_clip_pos.y);
    max_depth.y = XRender::SampleShadowMap(light_clip_pos.x, light_clip_pos.y + invert_size.y);
    //diff
    const Vec2f& diff = max_depth - min_depth;
    float gradient = std::min(XRender::ShadowSetting::gradient_diff_min, std::max(fabs(diff.x), fabs(diff.y)));
    float bias = gradient * XRender::ShadowSetting::gradient_scale_bias + XRender::ShadowSetting::const_bias * current_depth;
    
    float shadow = light_clip_pos.z > current_depth + bias ? 0.2 : 0;
    shadow += light_clip_pos.z > min_depth.x + bias ? 0.2 : 0;
    shadow += light_clip_pos.z > min_depth.y + bias ? 0.2 : 0;
    shadow += light_clip_pos.z > max_depth.x + bias ? 0.2 : 0;
    shadow += light_clip_pos.z > max_depth.y + bias ? 0.2 : 0;
    shadow *= XRender::ShadowSetting::shadow_strength;
    return 1 - shadow;
} 

    