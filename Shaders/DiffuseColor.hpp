#pragma once

#include "Shader.hpp"

namespace XRender::Shaders
{
    class DiffuseColor : public Shader
    {
        Sampler2D texture;
        void Init() override
        {
            BIND_VERTEX_INPUT(SEMANTIC::UV0);
            REGISTER_UNIFORM(Sampler2D, texture);
        }

        SET_PASIES()
        VERT_HEAD(vert1)
        {
            Vec4f pos = in.Get<Vec4f>(SEMANTIC::POSITION);
            Vec4f clip_pos = GraphicsGlobalData::matrix_mvp * pos;
            out.Set(SEMANTIC::SV_POSITION, clip_pos);

            Vec2f uv = in.Get<Vec2f>(SEMANTIC::UV0);
            out.Set(SEMANTIC::UV0, uv);
        };
        
        FRAGMENT_HEAD(frag1)
        {
            Vec2f uv = in.Get<Vec2f>(SEMANTIC::UV0);
            out = texture.Point(uv.x, uv.y);
        };

        AddPass("default", vert1, frag1);

        END_SET_PASIES()
    };
}