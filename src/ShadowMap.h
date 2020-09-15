#pragma once

#include "Lighting.h"
#include "Pipeline.h"

namespace XRender :: ShadowMap
{
    void Setup(Pipeline* pipeline);
    void Render();
    void Release();
}