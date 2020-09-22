
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
            BIND_VERTEX_INPUT(SEMANTIC::COLOR);
        }

        SET_PASIES()
        
        VERT_HEAD(vert)
        {
            Vec4f position = in.Get<Vec4f>(SEMANTIC::POSITION);
            Vec4f view_pos = GraphicsGlobalData::matrix_mv * position;
            Vec4f clip_pos = GraphicsGlobalData::matrix_p * view_pos;
            out.Set(SEMANTIC::SV_POSITION, clip_pos);
            Color color = in.Get<Color>(SEMANTIC::COLOR);
            out.Set(SEMANTIC::COLOR, color);

        };

        FRAGMENT_HEAD(frag) 
        {
            out = in.Get<Color>(SEMANTIC::COLOR); 
        };    

        AddPass("default", vert, frag);
        END_SET_PASIES()
    };
}