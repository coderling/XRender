#pragma once

#include "Shader.hpp"

namespace XRender::Shaders
{
    class DiffuseColor : public Shader
    {
        Sampler2D texture;
        void Init() override
        {
            BIND_VERTEXINPUT_SEMANTIC(SEMANTIC::UV0);
            BIND_VERTEXOUTPUT_SEMANTIC(SEMANTIC::UV0, Vec2f);
            REGISTER_UNIFORM(Sampler2D, texture);
        }

        VertexOutput Vertex(const VertexInput &in) override
        {
            VertexOutput out;
            Vec4f position;
            GET_DATA_BY_SEMATIC(position, in, SEMANTIC::POSITION);
            Vec4f view_pos = GraphicsGlobalData::matrix_mvp * position;
            FILL_SHADER_STRUCT(out, SEMANTIC::SV_POSITION, view_pos);

            Vec2f uv;
            GET_DATA_BY_SEMATIC(uv, in, SEMANTIC::UV0);
            FILL_SHADER_STRUCT(out, SEMANTIC::UV0, uv);
            return out;
        }

        void Fragment(const VertexOutput &in, Color &color) override
        {
            Vec2f uv; 
            GET_DATA_BY_SEMATIC(uv, in, SEMANTIC::UV0);
            color = texture.Point(uv.x, uv.y);
        }
    };
}