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
    Vec3f light_clip_pos = XRender::Math::TransformPoint(XRender::GraphicsGlobalData::matrix_shadow_light_vp, world_pos);
    // to [0, 1]
    light_clip_pos = (light_clip_pos + Vec3f_One) * 0.5f;
    const auto& invert_size = XRender::ShadowSetting::InvertSize();
    const auto& s_depth = XRender::SampleShadowMap(light_clip_pos.x, light_clip_pos.y);
    const auto& light_dir = XRender::GraphicsGlobalData::lights[XRender::GraphicsGlobalData::shadow_light_index]->forward;
    static float bias = std::max(shadow_bias, 0.05f * (1.0f - normal * light_dir));
    if(light_clip_pos.z - bias > s_depth)
    {
        return 0;
    }

    return 1;
} 

    