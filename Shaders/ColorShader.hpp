#pragma once

#include "Shader.hpp"

namespace XRender::Shaders
{
    class ColorShader : public Shader
    {
        void Init() override
        {
            BIND_VERTEX_INPUT(SEMANTIC::COLOR);
        }

        SET_PASIES()

        VERT_HEAD(vert)
        {
            const Vec4f& position = in.Get<Vec4f>(SEMANTIC::POSITION);
            Vec4f clip_pos = GraphicsGlobalData::matrix_mvp * position;
            out.Set(SEMANTIC::SV_POSITION, clip_pos);
            const Color& color  = in.Get<Color>(SEMANTIC::COLOR);
            out.Set(SEMANTIC::COLOR, color);
        };

        FRAGMENT_HEAD(frag)
        {
            out = in.Get<Color>(SEMANTIC::COLOR);
        };
        END_SET_PASIES()
    };
}