#pragma once
#include "PostProcessContext.h"

namespace XRender
{
    class PostProcessEffect
    {
    public:
        virtual ~PostProcessEffect();
        virtual void Render(PostProcessContext* context) = 0;
    };
}