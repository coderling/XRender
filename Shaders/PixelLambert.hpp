
#include "Shader.hpp"
#include "Lighting.hpp"

namespace XRender::Shaders
{
    class PixelLambert : public Shader
    {
        Sampler2D texture;
        Color color = CColor::GREY;
        void Init() override
        {
            BIND_VERTEX_INPUT(SEMANTIC::UV0);
            BIND_VERTEX_INPUT(SEMANTIC::NORMAL);
            REGISTER_UNIFORM(Sampler2D, texture);
            REGISTER_UNIFORM(Color, color);
        }

        SET_PASIES()

        VERT_HEAD(vert)
        {
            const Vec4f& position = in.Get<Vec4f>(SEMANTIC::POSITION);
            const Vec4f& clip_pos = GraphicsGlobalData::matrix_mvp * position;
            out.Set(SEMANTIC::SV_POSITION, clip_pos);

            const Vec2f& uv = in.Get<Vec2f>(SEMANTIC::UV0);
            out.Set(SEMANTIC::UV0, uv);

            const Vec3f& normal = in.Get<Vec3f>(SEMANTIC::NORMAL);
            const auto& world_normal = GraphicsGlobalData::matrix_m * embed<4>(normal, 0.f);
            out.Set(SEMANTIC::NORMAL, world_normal);
            const Vec4f& world_pos = GraphicsGlobalData::matrix_m * position;
            out.Set(SEMANTIC::POSITION, embed<3>(world_pos));
        };

        FRAGMENT_HEAD(frag)
        {
            
            const Vec3f& world_pos = in.Get<Vec3f>(SEMANTIC::POSITION);
            Vec3f normal = in.Get<Vec3f>(SEMANTIC::NORMAL);
            normal.normalize();

            out = CColor::BLACK; 
            for(uint32_t index = 0; index < GraphicsGlobalData::light_count; ++index)
            {
                out = out+ LightingLambert(*(GraphicsGlobalData::lights[index]), world_pos, normal);
            }

            const Vec2f& uv = in.Get<Vec2f>(SEMANTIC::UV0);
            out = color * out * ComputeShadow(world_pos, normal) * texture.Point(uv.x, uv.y);
        };

        AddPass("default", vert, frag);

        VERT_HEAD(shadow_vert)
        {
            const Vec4f& position = in.Get<Vec4f>(SEMANTIC::POSITION);
            const Vec4f& clip_pos = GraphicsGlobalData::matrix_mvp * position;
            out.Set(SEMANTIC::SV_POSITION, clip_pos);
        };

        FRAGMENT_HEAD(shadow_frag)
        {
            out = CColor::BLACK; 
        };

        AddPass(shadow_pass_name, shadow_vert, shadow_frag);
        END_SET_PASIES()
    };
}