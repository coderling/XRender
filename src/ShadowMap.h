#pragma once

#include "Lighting.h"
#include "Pipeline.h"
#include "Camera.h"

namespace XRender :: ShadowMap
{
    void Setup(Pipeline* pipeline);
    void Render(const Camera* camrea);
    void Release();
}