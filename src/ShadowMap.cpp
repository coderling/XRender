#include <memory>
#include <algorithm>

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

static XRender::Pipeline* current_pipeline = nullptr;

static const XRender::Lighting::LightData* use_light = nullptr;

float* depth_buffer = nullptr;
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
    depth_buffer = new float[depth_buffer_size];
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
    uint32_t width = XRender::ShadowSetting::width;
    uint32_t height = XRender::ShadowSetting::height;
    unsigned char depth;
    for(uint32_t y = 0; y < height; ++y)
    {
        uint32_t cy = height - y - 1;
        for(uint32_t x = 0; x < width; ++x)
        {
            depth = static_cast<unsigned char>(std::round(depth_buffer[y * width + x] * 255));
            color[0] = color[1] = color[2] = color[3] = depth;
            debug_out->set(x, cy, color);
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

    Vec4f n_topright(n_w, n_h, near, 1);
    n_topright =  camera->ViewMatrix() * n_topright;
    Vec4f n_topleft(-n_w, n_h, near, 1);
    n_topleft = camera->ViewMatrix() * n_topleft ;
    Vec4f n_bottomright(n_w, -n_h, near, 1);
    n_bottomright =  camera->ViewMatrix() * n_bottomright ;
    Vec4f n_bottomleft(-n_w, -n_h, near, 1);
    n_bottomleft =  camera->ViewMatrix() * n_bottomleft ;
    
    Vec4f f_topright(f_w, f_h, far, 1);
    f_topright = camera->ViewMatrix() * f_topright ;
    Vec4f f_topleft(-f_w, f_h, far, 1);
    f_topleft = camera->ViewMatrix() * f_topleft ;
    Vec4f f_bottomright(f_w, -f_h, far, 1);
    f_bottomright =  camera->ViewMatrix() *f_bottomright  ;
    Vec4f f_bottomleft(-f_w, -f_h, far, 1);
    f_bottomleft = camera->ViewMatrix() * f_bottomleft ;

    camera_bounds.center = embed<3>(n_topright / n_topright.w);
    camera_bounds.extents = Vec3f_Zero;
    camera_bounds.Expand(embed<3>(n_topleft/ n_topleft.w));
    camera_bounds.Expand(embed<3>(n_bottomright/ n_bottomright.w));
    camera_bounds.Expand(embed<3>(n_bottomleft/ n_bottomleft.w));
    camera_bounds.Expand(embed<3>(f_topright/ f_topright.w));
    camera_bounds.Expand(embed<3>(f_topleft/ f_topleft.w));
    camera_bounds.Expand(embed<3>(f_bottomright/ f_bottomright.w));
    camera_bounds.Expand(embed<3>(f_bottomleft/ f_bottomleft.w));
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
    //const auto& scene_bounds = current_pipeline->scene->GetSceneBounds();
    GetCameraBounds(camera);

    const Vec3f& position = camera_bounds.center - use_light->forward * camera_bounds.extents.norm();

    light_view = XRender::Math::CameraLookAt(embed<3>(position), use_light->up, use_light->forward);
    
    const auto& center = Math::TransformPoint(light_view, camera_bounds.center);
    const Vec3f& min = center - camera_bounds.extents;
    const Vec3f& max = center + camera_bounds.extents;
    light_proj = XRender::Math::CaculateOrthgraphic(min.x, max.x, max.y, min.y, min.z, max.z);

    SetViewPort();

    GraphicsGlobalData::zbuffer_args.x = 1 - max.z / min.z;
    GraphicsGlobalData::zbuffer_args.y = max.z / min.z;
    GraphicsGlobalData::matrix_v = light_view;
    GraphicsGlobalData::matrix_p = light_proj;
    GraphicsGlobalData::matrix_vp = light_proj * light_view;
    GraphicsGlobalData::matrix_viewport = light_viewport;
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
    Graphics::VirtualGraphic().SetClearFlag(GraphicsEnum::EClearFlag::Clear_Depth);
    Graphics::VirtualGraphic().Execute();
    CopyDepth(depth_buffer, depth_buffer_size);
    DebugPresentLightDepth();
}

void XRender::Lighting::ShadowMap::Release()
{
    use_light = nullptr;
    if(depth_buffer != nullptr)
    {
        delete [] depth_buffer;
    }
}