#pragma once
#include "GraphicsGlobalData.h"

namespace XRender
{
    void CopyDepth(float* buffer, const uint32_t& size);
    float SampleShadowMap(const float& u, const float& v);
}
