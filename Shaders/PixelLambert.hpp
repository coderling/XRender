
#include "Shader.hpp"
#include "Lighting.hpp"

namespace XRender::Shaders
{
    class PixelLambert : public Shader
    {
        Sampler2D texture;
        void Init() override
        {
            BIND_VERTEXINPUT_SEMANTIC(SEMANTIC::UV0);
            BIND_VERTEXINPUT_SEMANTIC(SEMANTIC::NORMAL);

            BIND_VERTEXOUTPUT_SEMANTIC(SEMANTIC::POSITION, Vec3f);
            BIND_VERTEXOUTPUT_SEMANTIC(SEMANTIC::NORMAL, Vec3f);
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

            Vec3f normal;
            GET_DATA_BY_SEMATIC(normal, in, SEMANTIC::NORMAL);
            auto world_normal = GraphicsGlobalData::matrix_m * embed<4>(normal, 0.f);
            FILL_SHADER_STRUCT(out, SEMANTIC::NORMAL,  embed<3>(world_normal));

            Vec4f world_pos = GraphicsGlobalData::matrix_m * position;
            FILL_SHADER_STRUCT(out, SEMANTIC::POSITION, embed<3>(world_pos));
            return out;
        }

        void Fragment(const VertexOutput &in, Color &color) override
        {
            Vec3f world_pos;
            GET_DATA_BY_SEMATIC(world_pos, in, SEMANTIC::POSITION);
            Vec3f normal;
            GET_DATA_BY_SEMATIC(normal, in, SEMANTIC::NORMAL);
            normal.normalize();

            color = CColor::BLACK; 
            for(uint32_t index = 0; index < GraphicsGlobalData::light_count; ++index)
            {
                color = color + LightingLambert(*(GraphicsGlobalData::lights[index]), world_pos, normal);
            }

            Vec2f uv; 
            GET_DATA_BY_SEMATIC(uv, in, SEMANTIC::UV0);
            color = color * texture.Point(uv.x, uv.y);
        }
    };
}