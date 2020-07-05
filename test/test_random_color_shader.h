#include <cmath>
#include <string>

#include "Pipeline.h"

namespace XRender::Test
{
    class RandomColor : public Shader
    {
        void Init() override
        {
            BIND_VERTEXOUTPUT_SEMANTIC(SEMANTIC::COLOR, Color);
        }

        VertexOutput Vertex(const VertexInput &in) override
        {
            VertexOutput out;
            Vec4f position;
            GET_DATA_BY_SEMATIC(position, in, SEMANTIC::POSITION, Vec4f);
            Vec4f view_pos = GraphicsGlobalData::matrix_mvp * position;
            FILL_SHADER_STRUCT(out, SEMANTIC::SV_POSITION, view_pos);
            int rand_r = std::rand() % 255;
            int rand_g = std::rand() % 255;
            int rand_b = std::rand() % 255;
            Color color;
            color.r = rand_r / 255.f;            
            color.g = rand_g / 255.f;            
            color.b = rand_b / 255.f;            
            color.a = 1;
            FILL_SHADER_STRUCT(out, SEMANTIC::COLOR, color);
            return out;
        }

        void Fragment(const VertexOutput &in, Color &color) override
        {
            GET_DATA_BY_SEMATIC(color, in, SEMANTIC::COLOR, Color);
        }
    };
}