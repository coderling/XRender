#include <cmath>
#include <string>

#include "Pipeline.h"

namespace XRender::Test
{
    class RandomColor : public Shader
    {
        Sampler2D texture;
        void Init() override
        {
            //REGISTER_UNIFORM(Sampler2D, texture);
        }

        VertexOutput Vertex(const VertexInput &in) override
        {
            VertexOutput out;
            Vec4f position;
            GET_DATA_BY_SEMATIC(position, in, SEMANTIC::POSITION);
            Vec4f view_pos = GraphicsGlobalData::matrix_mvp * position;
            FILL_SHADER_STRUCT(out, SEMANTIC::SV_POSITION, view_pos);
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