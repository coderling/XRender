#pragma once
#include <algorithm>

#include "../../src/GraphicsGlobalData.h"
#include "../../src/Lighting.h"
#include "../../src/Color.h"

const float light_atten_factor1 = 4;
const float light_atten_factor2 = 4;

inline float LightAttenaution(const XRender::Lighting::LightData& light, const Vec3f& world_pos)
{
    if(light.world_pos.w < 1e-2)
    {
        return 1;
    }

    Vec3f dir = embed<3>(light.world_pos) - world_pos;
    float dd = dir.x * dir.x + dir.y * dir.y + dir.z * dir.z;
    float d = std::sqrt(dd);
 
    if (d > light.range) return 0;

    return 1.0f / (1.0f + light_atten_factor1 * d + light_atten_factor2 * d);
}

inline Vec3f LightDir(const XRender::Lighting::LightData& light, const Vec3f& world_pos)
{
    return embed<3>(light.world_pos) - world_pos * light.world_pos.w;
}

inline XRender::Color LightingLambert(const XRender::Lighting::LightData& light, const Vec3f& world_pos, const Vec3f& normal)
{
    Vec3f light_dir = LightDir(light, world_pos) * -1;
    light_dir.normalize();
    float diffuse = std::max(0.f, normal * light_dir);
    return light.color * diffuse * LightAttenaution(light, world_pos) * light.intensity;
}

