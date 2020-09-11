
#include "Pipeline.h"

namespace XRender::Test
{
    #define BeginShader(type_name)\
        class type_name : public Shader\
        {\


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
            Vec4f view_pos = GraphicsGlobalData::matrix_mv * position;
            Vec4f clip_pos = GraphicsGlobalData::matrix_p * view_pos;
            FILL_SHADER_STRUCT(out, SEMANTIC::SV_POSITION, clip_pos);
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