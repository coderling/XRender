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

XRender::Bounds GetCameraBounds(const XRender::Camera camera)
{
    XRender::Bounds camera_bounds;

    return camera_bounds;
}

void UpdateViewSpace(const XRender::Camera* camera)
{
    //const auto& scene_bounds = current_pipeline->scene->GetSceneBounds();
}

void XRender::ShadowMap::Setup(XRender::Pipeline* pipeline) 
{
    assert(pipeline != nullptr);
    current_pipeline = pipeline; 
}

void XRender::ShadowMap::Render(const Camera* camera)
{
    if (!ShadowSetting::enable_shadow)
        return;
    PrePare();

    if(use_light == nullptr)
        return;

    UpdateViewSpace(camera);
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