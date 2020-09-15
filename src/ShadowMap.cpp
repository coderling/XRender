#include "ShadowMap.h"
#include "GraphicsGlobalData.h"
#include "ShadowSetting.h"
#include "Graphics.h"
#include "GraphicsEnum.h"

static XRender::Pipeline* current_pipeline = nullptr;

static const XRender::Lighting::LightData* use_light = nullptr;

float* depth_buffer = nullptr;

static Matrix light_proj;

void CreateDepthBuffer()
{
   if(use_light == nullptr || depth_buffer != nullptr)
   {
       return;
   }

   depth_buffer =  new float[XRender::ShadowSetting::width * XRender::ShadowSetting::height];
}

void PrePare() 
{
    use_light = nullptr;
    for(uint32_t index = 0; index < XRender::GraphicsGlobalData::light_count; ++index)
    {
        auto light = XRender::GraphicsGlobalData::lights[index];
        if(use_light == nullptr || (light->intensity > use_light->intensity && light->world_pos.w == 0))
        {
            use_light = light;
        }
    }
    CreateDepthBuffer();
}

void UpdateViewSpace()
{

}

void XRender::ShadowMap::Setup(XRender::Pipeline* pipeline) 
{
    assert(pipeline != nullptr);
    current_pipeline = pipeline; 
}

void XRender::ShadowMap::Render()
{
    if (!ShadowSetting::enable_shadow)
        return;
    PrePare();

    if(use_light == nullptr)
        return;

    UpdateViewSpace();
    Graphics::VirtualGraphic().SetClearFlag(GraphicsEnum::EClearFlag::Clear_Depth);
    Graphics::VirtualGraphic().Execute();
}

void XRender::ShadowMap::Release()
{
    use_light = nullptr;
    if(depth_buffer != nullptr)
    {
        delete [] depth_buffer;
    }
}