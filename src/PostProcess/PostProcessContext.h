#pragma once
#include "../Camera.h"

namespace XRender
{
    class PostProcessContext final
    {
    public:
        Camera* camera = nullptr;
        RenderContext* render_context = nullptr;
    };
}