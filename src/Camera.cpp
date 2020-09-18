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
    is_perspective = true;
    angle = 60;
    aspect = 1;
    near_plane = 0.1f;
    far_plane = 1000.f;
}

const Matrix& XRender::Camera::ViewMatrix() const
{
    return view;
}
    
const Matrix& XRender::Camera::InvertViewMatrix() const
{
    return invert_view;
}

const Matrix& XRender::Camera::ProjMatrix() const
{
    return proj;
}

void XRender::Camera::LookAt(const Vec3f& pos, const Vec3f& up, const Vec3f& target)
{
    view = Math::CameraLookAt(pos, up, target - pos);
    invert_view = view.invert();
    transform.SetPosition(pos);
    transform.SetRotation(Math::RotateToEuler(view)); 
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

void XRender::Camera::CaculatePerspective()
{
    auto device = RenderDevice::Device();
    assert(device != nullptr);
    this->aspect = device->GetWidth() * 1.0f / device->GetHeight();
    proj = Math::Perspective(angle, aspect, near_plane, far_plane);
}

void XRender::Camera::CaculateOrthgraphic()
{
    auto device = RenderDevice::Device();
    assert(device != nullptr);
    int width = device->GetWidth();
    int height = device->GetHeight();
    float left = width * 1.f / 2;
    float right = -left;
    float top = height * 1.f / 2;
    float bottom = -top;
    proj = Math::CaculateOrthgraphic(left, right, top, bottom, near_plane, far_plane);
}

void XRender::Camera::SetViewPort(const float &x, const float &y, const float &w, const float &h)
{
    auto device = RenderDevice::Device();
    assert(device != nullptr);
    int width = device->GetWidth();
    int height = device->GetHeight();
    int ix = (int)(width * x);
    int iy = (int)(height * y);
    int iw = (int)(width * w);
    int ih = (int)(height * h);

    view_port = Matrix::identity();
    view_port[0][3] = ix + iw / 2.0f;
    view_port[1][3] = iy + ih / 2.0f;
    view_port[2][3] = 0;
    
    view_port[0][0] = iw / 2.0f;
    view_port[1][1] = ih / 2.0f;
    view_port[2][2] = 1;
}

void XRender::Camera::Update()
{
    frustum.Update(proj * view);
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
}

const XRender::Frustum& XRender::Camera::GetFrustum() const
{
    return frustum;
}

void XRender::Camera::Present()
{
    Graphics::VirtualGraphic().Present();
}

const XRender::Transform& XRender::Camera::Transform() const
{
    return transform;
}
    
const float& XRender::Camera::Near() const
{
    return near_plane;
}

const float& XRender::Camera::Far() const
{
    return far_plane;
}

const float& XRender::Camera::Angle() const
{
    return angle;
}

void XRender::Camera::Near(const float& near)
{
    near_plane = near;
    ReCaculateProjectMatrix();
}

void XRender::Camera::Far(const float& far)
{
    far_plane = far;
    ReCaculateProjectMatrix();
}

void XRender::Camera::Angle(const float& angle)
{
    this->angle = angle;
    ReCaculateProjectMatrix();
}

void XRender::Camera::IsPerspective(const bool& isPerProj)
{
    if(this->is_perspective != isPerProj)
    {
        this->is_perspective = isPerProj;
        ReCaculateProjectMatrix();
    }
}

const bool& XRender::Camera::IsPerspective()
{
    return is_perspective;
}

const float& XRender::Camera::Aspect()const
{
    return aspect;
}