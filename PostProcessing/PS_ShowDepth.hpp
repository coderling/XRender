#pragma once
#include <iostream>

#include "PostProcessInc.h"

namespace XRender::PostProcessing
{
    class PS_ShowDepth final : public PostProcessEffect
    {
    public:
        void Render(PostProcessContext* context) override
        {
            uint32_t w = context->render_context->GetWidth();
            uint32_t h = context->render_context->GetHeight();
            for(uint32_t i = 0; i < w; ++i)
            {
                for(uint32_t j = 0; j < h; ++j)
                {
                    Color col;
                    col.a = 1;
                }
            }
        }
    };
}