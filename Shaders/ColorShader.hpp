#pragma once

#include "Shader.hpp"

namespace XRender::Shaders
{
    class ColorShader : public Shader
    {
        void Init() override
        {
            BIND_VERTEXINPUT_SEMANTIC(SEMANTIC::COLOR);
            BIND_VERTEXOUTPUT_SEMANTIC(SEMANTIC::COLOR, Color);
        }

        VertexOutput Vertex(const VertexInput& in) override
        {
            VertexOutput out;
            Vec4f position;
            GET_DATA_BY_SEMATIC(position, in, SEMANTIC::POSITION);
            Vec4f view_pos = GraphicsGlobalData::matrix_mvp * position;
            FILL_SHADER_STRUCT(out, SEMANTIC::SV_POSITION, view_pos);
            Color color;
            GET_DATA_BY_SEMATIC(color, in, SEMANTIC::COLOR);
            FILL_SHADER_STRUCT(out, SEMANTIC::COLOR, color);
            return out;
        }

        void Fragment(const VertexOutput& in, Color& color) override
        {
            GET_DATA_BY_SEMATIC(color, in, SEMANTIC::COLOR);
        }
    };
}