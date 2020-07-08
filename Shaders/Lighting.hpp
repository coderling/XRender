#pragma once

#include "../../src/GraphicsGlobalData.h"
#include "../../src/Lighting.h"
#include "../../src/Color.h"

inline const XRender::Lighting::LightData& GetLight()
{
    auto light = XRender::GraphicsGlobalData::light;
    if(light == nullptr)
    {
        return XRender::Lighting::null_light;
    }

    return *light;
}

inline float LightAttenaution(const XRender::Lighting::LightData& light, const Vec3f& shading_pos)
{
    return 1;
}

inline XRender::Color LightingLambert(const Vec3f& shading_pos, const Vec3f& normal, const Vec3f& light_direction)
{
    return XRender::CColor::BLACK;
}

