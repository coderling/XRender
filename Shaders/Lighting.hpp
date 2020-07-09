#pragma once
#include <algorithm>

#include "../../src/GraphicsGlobalData.h"
#include "../../src/Lighting.h"
#include "../../src/Color.h"

inline float LightAttenaution(const XRender::Lighting::LightData& light, const Vec3f& world_pos)
{
    if(light.world_pos.w < 1e-2)
    {
        return 1;
    }
    return 1;
    Vec3f dis = embed<3>(light.world_pos) - world_pos;
    return 1.0f / std::sqrt(dis.x * dis.x + dis.y * dis.y + dis.z * dis.z);
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

