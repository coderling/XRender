#include "ShadowMap.h"
#include "GraphicsGlobalData.h"
#include "ShadowSetting.h"
#include "Graphics.h"
#include "GraphicsEnum.h"

static const XRender::Lighting::LightData* use_light = nullptr;

float* depth_buffer = nullptr;

void CreateDepthBuffer()
{
   if(use_light == nullptr || depth_buffer == nullptr)
   {
       return;
   }

   depth_buffer =  new float[XRender::ShadowSetting::width * XRender::ShadowSetting::height];
}

void XRender::ShadowMap::Setup() 
{
    use_light = nullptr;
    for(uint32_t index = 0; index < GraphicsGlobalData::light_count; ++index)
    {
        auto light = GraphicsGlobalData::lights[index];
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

void XRender::ShadowMap::Render()
{
    if (!ShadowSetting::enable_shadow)
        return;
    Setup();
    UpdateViewSpace();
    Graphics::VirtualGraphic().SetClearFlag(GraphicsEnum::EClearFlag::Clear_Depth);
    Graphics::VirtualGraphic().SetDepthOnlyMode(true);
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