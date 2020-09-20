#include <memory>

#include "ShadowMap.h"
#include "GraphicsGlobalData.h"
#include "ShadowSetting.h"
#include "Graphics.h"
#include "GraphicsEnum.h"
#include "math/Math.h"
#include "RenderTexture.h"

static XRender::Pipeline* current_pipeline = nullptr;

static const XRender::Lighting::LightData* use_light = nullptr;

std::unique_ptr<XRender::RenderTexture> depth_buffer = nullptr;

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

   //depth_buffer.reset(buffer);
}

void GetCameraBounds(const XRender::Camera* camera)
{
    camera_bounds.Zero();
    float near = camera->Near();
    float far = XRender::ShadowSetting::shadow_distance;
    if(far <= near)
        return;

    float fov = camera->Angle() / 2;
    float n_h = near * tan(fov);
    float n_w = n_h * camera->Aspect();
    float fdn = far / near;
    float f_h = fdn * n_h;
    float f_w = fdn * n_w;

    Vec4f n_topright(near, n_h, n_w, 1);
    n_topright =  camera->InvertViewMatrix() * n_topright;
    Vec4f n_topleft(near, n_h, -n_w, 1);
    n_topleft = camera->InvertViewMatrix() * n_topleft ;
    Vec4f n_bottomright(near, -n_h, n_w, 1);
    n_bottomright =  camera->InvertViewMatrix() * n_bottomright ;
    Vec4f n_bottomleft(near, -n_h, -n_w, 1);
    n_bottomleft =  camera->InvertViewMatrix() * n_bottomleft ;
    
    Vec4f f_topright(far, f_h, f_w, 1);
    f_topright = camera->InvertViewMatrix() * f_topright ;
    Vec4f f_topleft(far, f_h, -f_w, 1);
    f_topleft = camera->InvertViewMatrix() * f_topleft ;
    Vec4f f_bottomright(far, -f_h, f_w, 1);
    f_bottomright =  camera->InvertViewMatrix() *f_bottomright  ;
    Vec4f f_bottomleft(far, -f_h, -f_w, 1);
    f_bottomleft = camera->InvertViewMatrix() * f_bottomleft ;

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
    light_view = XRender::Math::CameraLookAt(embed<3>(use_light->position), use_light->up, use_light->forward);
    
    const Vec3f& min = Math::TransformPoint(light_view, camera_bounds.Min());
    const Vec3f& max = Math::TransformPoint(light_view, camera_bounds.Max());
    light_proj = XRender::Math::CaculateOrthgraphic(min.x, max.x, max.y, min.x, min.z, max.z);

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
        if(use_light == nullptr || (light->intensity > use_light->intensity && light->world_pos.w == 0))
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
}

void XRender::Lighting::ShadowMap::Release()
{
    use_light = nullptr;
    depth_buffer = nullptr;
}