#include <memory>
#include <algorithm>
#include <iostream>

#include <tgaimage.h>

#include "ShadowMap.h"
#include "GraphicsGlobalData.h"
#include "ShadowSetting.h"
#include "Graphics.h"
#include "GraphicsUtils.h"
#include "GraphicsEnum.h"
#include "math/Math.h"
#include "RenderTexture.h"
#include "math/Math.h"

static bool debug = true;

static std::unique_ptr<TGAImage> debug_out = nullptr;
static bool debug_out_depth = true;
static int clear_flag = debug_out_depth ? XRender::GraphicsEnum::EClearFlag::Clear_Depth : (XRender::GraphicsEnum::EClearFlag::Clear_Depth | XRender::GraphicsEnum::EClearFlag::Clear_Color);
static XRender::GraphicsEnum::ERenderTargetFormat shadow_map_format = debug_out_depth ? XRender::GraphicsEnum::ERenderTargetFormat::ShadowMap : XRender::GraphicsEnum::ERenderTargetFormat::Default;

static XRender::Pipeline* current_pipeline = nullptr;

static const XRender::Lighting::LightData* use_light = nullptr;

static std::unique_ptr<XRender::RenderTexture> depth_buffer = nullptr;
static uint32_t depth_buffer_size = 0;

static Matrix light_proj;
static Matrix light_view;
static Matrix light_viewport;
    
static XRender::Bounds camera_bounds;

void CreateDepthBuffer()
{
   if(use_light == nullptr || depth_buffer != nullptr)
   {
       return;
   }
    depth_buffer_size = XRender::ShadowSetting::width * XRender::ShadowSetting::height;
    depth_buffer = XRender::RenderTexture::CreateRenderTarget(XRender::ShadowSetting::width, XRender::ShadowSetting::height, true, shadow_map_format);
    if(debug && debug_out == nullptr)
    {
        debug_out = std::make_unique<TGAImage>(XRender::ShadowSetting::width, XRender::ShadowSetting::height, TGAImage::RGB);
    }
}

void DebugPresentLightDepth()
{
    if(debug_out == nullptr)
        return;

    TGAColor color;
    XRender::Color32 color32;
    uint32_t width = XRender::ShadowSetting::width;
    uint32_t height = XRender::ShadowSetting::height;
    unsigned char depth;
    for(uint32_t y = 0; y < height; ++y)
    {
        uint32_t cy = height - y - 1;
        for(uint32_t x = 0; x < width; ++x)
        {
            if (debug_out_depth)
            {
                depth = static_cast<unsigned char>(std::round(depth_buffer->DepthOf(x, cy) * 255));
                color[0] = color[1] = color[2] = depth; color[3] = 255;
            }
            else
            {
                depth_buffer->ReadPixel(x, cy, color32);
                color[2] = color32.r;
                color[1] = color32.g;
                color[0] = color32.b;
                color[3] = color32.a;
            }
            debug_out->set(x, y, color);
        }
    }

    debug_out->write_tga_file("ImageOut/debug_shadowmap.tga");
}

void GetCameraBounds(const XRender::Camera* camera)
{
    camera_bounds.Zero();
    float near = camera->Near();
    float far = XRender::ShadowSetting::shadow_distance;
    if(far <= near)
        return;

    float fov = camera->Angle() / 2;
    float n_h = near * tan(fov * XRender::Math::PI_DEGREE);
    float n_w = n_h * camera->Aspect();
    float fdn = far / near;
    float f_h = fdn * n_h;
    float f_w = fdn * n_w;
    
    const Matrix& invertView = light_view * camera->InvertViewMatrix();
    const auto& n_topright = XRender::Math::TransformPoint(invertView, Vec3f(n_w, n_h, -near));
    const auto& n_topleft = XRender::Math::TransformPoint(invertView, Vec3f(-n_w, n_h, -near));
    const auto& n_bottomright = XRender::Math::TransformPoint(invertView, Vec3f(n_w, -n_h, -near));
    const auto& n_bottomleft = XRender::Math::TransformPoint(invertView, Vec3f(-n_w, -n_h, -near));
    
    const auto& f_topright = XRender::Math::TransformPoint(invertView, Vec3f(f_w, f_h, -far));
    const auto& f_topleft = XRender::Math::TransformPoint(invertView, Vec3f(-f_w, f_h, -far));
    const auto& f_bottomright = XRender::Math::TransformPoint(invertView, Vec3f(f_w, -f_h, -far));
    const auto& f_bottomleft = XRender::Math::TransformPoint(invertView, Vec3f(-f_w, -f_h, -far));
    
    camera_bounds.center = n_topright;
    camera_bounds.extents = Vec3f_Zero;
    camera_bounds.Expand(n_topleft);
    camera_bounds.Expand(n_bottomright);
    camera_bounds.Expand(n_bottomleft);
    camera_bounds.Expand(f_topright);
    camera_bounds.Expand(f_topleft);
    camera_bounds.Expand(f_bottomright);
    camera_bounds.Expand(f_bottomleft);
}

void SetViewPort()
{
    
    int ix = 0;
    int iy = 0;
    int iw = XRender::ShadowSetting::width;
    int ih = XRender::ShadowSetting::height;

    Matrix::identity(light_viewport);
    light_viewport[0][3] = ix + iw / 2.0f;
    light_viewport[1][3] = iy + ih / 2.0f;
    light_viewport[2][3] = 0;
    
    light_viewport[0][0] = iw / 2.0f;
    light_viewport[1][1] = ih / 2.0f;
    light_viewport[2][2] = 1;
}

void XRender::Lighting::ShadowMap::UpdateViewSpace(const XRender::Camera* camera)
{

    const Vec3f& position = camera->Transform().GetPosition() - use_light->forward * 9999999;
    light_view = XRender::Math::CameraLookAt(embed<3>(position), use_light->up, Vec3f_Zero - use_light->forward);
    GetCameraBounds(camera);
    
    const Vec3f& c_min = camera_bounds.Min();
    const Vec3f& c_max = camera_bounds.Max();
    
    static Vec3f min;
    static Vec3f max;

    min.x = std::min(c_min.x, c_max.x);
    min.y = std::min(c_min.y, c_max.y);
    max.x = std::max(c_min.x, c_max.x);
    max.y = std::max(c_min.y, c_max.y);
    
    const auto& scene_bounds = current_pipeline->scene->GetSceneBounds();
    const auto& scene_center = Math::TransformPoint(light_view, scene_bounds.center);
    const Vec3f& sm1 =  Math::TransformPoint(light_view, scene_bounds.Min());
    const Vec3f& sm2 =  Math::TransformPoint(light_view, scene_bounds.Max());
    min.z = -std::max(sm1.z, sm2.z);
    max.z = -std::min(sm1.z, sm2.z);


    light_proj = XRender::Math::CaculateOrthgraphic(min.x, max.x, min.y, max.y, min.z, max.z);

    SetViewPort();

    GraphicsGlobalData::zbuffer_args.x = 1 - max.z / min.z;
    GraphicsGlobalData::zbuffer_args.y = max.z / min.z;
    GraphicsGlobalData::matrix_v = light_view;
    GraphicsGlobalData::matrix_p = light_proj;
    GraphicsGlobalData::matrix_vp = light_proj * light_view;
    GraphicsGlobalData::matrix_viewport = light_viewport;
    GraphicsGlobalData::matrix_shadow_light_vp= GraphicsGlobalData::matrix_vp;
}

void XRender::Lighting::ShadowMap::Setup(XRender::Pipeline* pipeline) 
{
    assert(pipeline != nullptr);
    current_pipeline = pipeline; 
}

void XRender::Lighting::ShadowMap::PrePare() 
{
    use_light = nullptr;
    for(uint32_t index = 0; index < XRender::GraphicsGlobalData::light_count; ++index)
    {
        auto light = XRender::GraphicsGlobalData::lights[index];
        if(use_light == nullptr || (light->intensity > use_light->intensity && light->light_type == Lighting::LightType::Directional))
        {
            use_light = light;
            XRender::GraphicsGlobalData::shadow_light_index = index;
        }
    }
    CreateDepthBuffer();
}


void XRender::Lighting::ShadowMap::Render(const Camera* camera)
{
    if (!ShadowSetting::enable_shadow)
        return;
    PrePare();

    if(use_light == nullptr)
        return;

    UpdateViewSpace(camera);
    Graphics::VirtualGraphic().GetRenderContext()->ActiveTarget(depth_buffer.get());
    Graphics::VirtualGraphic().SetClearFlag(clear_flag);
    Graphics::VirtualGraphic().Execute(!debug || debug_out_depth);
    DebugPresentLightDepth();
    Graphics::VirtualGraphic().GetRenderContext()->ActiveTarget(nullptr);
}

void XRender::Lighting::ShadowMap::Release()
{
    use_light = nullptr;
    depth_buffer = nullptr;
}
        
float XRender::Lighting::ShadowMap::SampleShadowMap(const float& u, const float& v)
{
    const auto& x = (ShadowSetting::width -1) * u;
    const auto& y = (ShadowSetting::height -1)* v;
    assert(x < ShadowSetting::width && y < ShadowSetting::height);
    return depth_buffer->DepthOf(x, y);
}