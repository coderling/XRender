
#include "Pipeline.h"

namespace XRender::Test
{
    class ColorShader : public Shader
    {
        void Init() override
        {
        }

        VertexOutput Vertex(const VertexInput& in) override
        {
            VertexOutput out;
            Vec4f position;
            GET_DATA_BY_SEMATIC(position, in, SEMANTIC::POSITION, Vec4f);
            Vec4f view_pos = GraphicsGlobalData::matrix_mvp * position;
            FILL_SHADER_STRUCT(out, SEMANTIC::SV_POSITION, view_pos);
            return out;
        }

        void Fragment(const VertexOutput& in, Color& color) override
        {
            color = CColor::RED;
        }
    };
}