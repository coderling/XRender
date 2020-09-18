#pragma once

#include "Lighting.h"
#include "Pipeline.h"
#include "Camera.h"
#include "NoCopyable.h"

namespace XRender::Lighting
{
    class ShadowMap final : NoCopyable 
    {
        static void Setup(Pipeline* pipeline);
        static void Render(const Camera* camrea);
        static void Release();
    private:
        static void PrePare();
        static void UpdateViewSpace(const XRender::Camera* camera);
    };
}