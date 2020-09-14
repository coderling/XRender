#include "Camera.h"
#include "Graphics.h"
#include "GraphicsGlobalData.h"

XRender::Camera& XRender::Camera::MainCamera()
{
	static Camera main_camera;
	return main_camera;
}

XRender::Camera::Camera()
{
    render_target = nullptr;
    is_perspective = true;
    angle = 60;
    near_plane = 0.1f;
    far_plane = 1000.f;
}

const Matrix& XRender::Camera::GetViewMatrix() const
{
    return view;
}

const Matrix& XRender::Camera::GetProjMatrix() const
{
    return proj;
}

void XRender::Camera::LookAt(const Vec3f& pos, const Vec3f& up, const Vec3f& look)
{
    view = Math::CameraLookAt(pos, up, look);
    invert_view = view.invert();
}

void XRender::Camera::SetIsPerspective(const bool& isPerProj)
{
    if (isPerProj != is_perspective)
    {
        is_perspective = isPerProj;
        ReCaculateProjectMatrix();
    }
}

void XRender::Camera::ReCaculateProjectMatrix()
{
    if(is_perspective)
    {
        CaculatePerspective();
        return;
    }

    CaculateOrthgraphic();
}

void XRender::Camera::SetFieldOfView(const float& angle)
{
    if(!is_perspective) return;
    this->angle = angle;
    CaculatePerspective();
}

void XRender::Camera::SetPerspective(const float &angle, const float &near, const float &far)
{
    this->angle = angle;
    this->near_plane = near;
    this->far_plane = far;
    is_perspective = true;
    if (render_target != nullptr)
      CaculatePerspective();
}

void XRender::Camera::CaculatePerspective()
{
    proj = Math::Perspective(angle, aspect, near_plane, far_plane);
}

void XRender::Camera::SetOrthgraphic(const float &near, const float &far)
{
    this->near_plane = near;
    this->far_plane = far;
    is_perspective = false;
    ReCaculateProjectMatrix();
}

void XRender::Camera::CaculateOrthgraphic()
{
    int width = render_target->GetWidth();
    int height = render_target->GetHeight();
    float left = width * 1.f / 2;
    float right = -left;
    float top = height * 1.f / 2;
    float bottom = -top;
    proj = Math::CaculateOrthgraphic(left, right, top, bottom, near_plane, far_plane);
}

void XRender::Camera::SetViewPort(const float &x, const float &y, const float &w, const float &h)
{
    assert(render_target != nullptr);
    int width = render_target->GetWidth();
    int height = render_target->GetHeight();
    int ix = (int)(width * x);
    int iy = (int)(height * y);
    int iw = (int)(width * w);
    int ih = (int)(height * w);

    view_port = Matrix::identity();
    view_port[0][3] = ix + iw / 2.0f;
    view_port[1][3] = iy + ih / 2.0f;
    view_port[2][3] = 0;
    
    view_port[0][0] = iw / 2.0f;
    view_port[1][1] = ih / 2.0f;
    view_port[2][2] = 1;
}

void XRender::Camera::SetRenderTarget(std::unique_ptr<RenderTarget> target)
{
    render_target = std::move(target);
    SetViewPort(0, 0, 1, 1);
    aspect = render_target->GetWidth() * 1.f / render_target->GetHeight();
    ReCaculateProjectMatrix();
}

void XRender::Camera::Update()
{
    frustum.Update(proj * view);
    render_target->OnUpdate();
}

void XRender::Camera::SyncGraphicsCameraData() const
{
    GraphicsGlobalData::zbuffer_args.x = 1 - far_plane / near_plane;
    GraphicsGlobalData::zbuffer_args.y = far_plane / near_plane;
    GraphicsGlobalData::matrix_v = this->view;
    GraphicsGlobalData::matrix_p = this->proj;
    GraphicsGlobalData::matrix_vp = this->proj * this->view;
    GraphicsGlobalData::matrix_viewport = this->view_port;
    Graphics::VirtualGraphic().SetClearFlag(clear_flag);
    Graphics::VirtualGraphic().SetDepthOnlyMode(false);
}

const XRender::Frustum& XRender::Camera::GetFrustum() const
{
    return frustum;
}

void XRender::Camera::Present()
{
    assert(Graphics::VirtualGraphic().GetContextWidth() == render_target->GetWidth());
    assert(Graphics::VirtualGraphic().GetContextHeight() == render_target->GetHeight());
    render_target->OnPresent(&Graphics::VirtualGraphic().GetRenderContext());
}
