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
    view = Matrix::identity();
    Vec3f lcp = cross(look, up);
    Vec3f t_up = cross(lcp, look);
    lcp.normalize();
    t_up.normalize();
    Vec3f lk = look;
    lk.normalize();

    view[0][0] = lcp.x;
    view[0][1] = lcp.y;
    view[0][2] = lcp.z;
    view[0][3] = lcp.x * -pos.x + lcp.y * -pos.y + lcp.z * -pos.z;

    view[1][0] = t_up.x;
    view[1][1] = t_up.y;
    view[1][2] = t_up.z;
    view[1][3] = t_up.x * -pos.x + t_up.y * -pos.y + t_up.z * -pos.z;
    
    view[2][0] = lk.x;
    view[2][1] = lk.y;
    view[2][2] = lk.z;
    view[2][3] = lk.x * -pos.x + lk.y * -pos.y + lk.z * -pos.z;
}

void XRender::Camera::SetIsPerspective(const bool& isPerProj)
{
    is_perspective = isPerProj;
    ReCaculateProjectMatrix();
}

void XRender::Camera::ReCaculateProjectMatrix()
{
    if(is_perspective)
    {
        CaculatePerspective();
        return;
    }

    int width = render_target->GetWidth();
    int height = render_target->GetHeight();
    float left = width * 1.f / 2;
    float right = -left;
    float top = height * 1.f / 2;
    float bottom = -top;
    proj = CaculateOrthgraphic(left, right, top, bottom, -near_plane, -far_plane);
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
    float top = near_plane * tan(angle * PI / 2.0f / 180.0f);
    float bottom = -top;
    float right = top * aspect;
    float left = -right;
    
    float near = -near_plane;
    float far = -far_plane;
    // 挤压到正交的视锥体, 再进行正交投影
    Matrix persToOrthMatrix = Matrix::identity();
    persToOrthMatrix[0][0] = near;
    persToOrthMatrix[1][1] = near;
    persToOrthMatrix[2][2] = near+ far;
    persToOrthMatrix[2][3] = -near * far;
	persToOrthMatrix[3][2] = 1;
	persToOrthMatrix[3][3] = 0;

    Matrix orth = CaculateOrthgraphic(left, right, top, bottom, near, far);

    proj = orth * persToOrthMatrix;
}

void XRender::Camera::SetOrthgraphic(const float &near, const float &far)
{
    this->near_plane = near;
    this->far_plane = far;
    is_perspective = false;
    ReCaculateProjectMatrix();
}

Matrix XRender::Camera::CaculateOrthgraphic(const float& left, const float& right, const float& top, const float& bottom, const float& near, const float& far) const
{
    // 先平移---》缩放到[-1, 1]的立方体内，方便裁剪
    Matrix transpose = Matrix::identity();
    transpose[0][3] = -(left + right) / 2;
    transpose[1][3] = -(bottom + top) / 2;
    transpose[2][3] = -(near + far) / 2;

    float xscale = 2 / (right - left);
    float yscale = 2 / (top - bottom);
    float zscale = 2 / (near - far);
    
    Matrix scaleMatrix = Matrix::identity();
    scaleMatrix[0][0] = xscale;
    scaleMatrix[1][1] = yscale;
    scaleMatrix[2][2] = zscale;

    return scaleMatrix * transpose;
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
    frustum.Update(proj);
    render_target->OnUpdate();
}

void XRender::Camera::SyncGraphicsCameraData() const
{
    GraphicsGlobalData::matrix_v = this->view;
    GraphicsGlobalData::matrix_p = this->proj;
    GraphicsGlobalData::matrix_vp = this->proj * this->view;
    GraphicsGlobalData::matrix_viewport = this->view_port;
}

const XRender::Frustum& XRender::Camera::GetFrustum() const
{
    return frustum;
}

void XRender::Camera::Present()
{
    assert(Graphics::VirtualGraphic().GetContextWidth() == render_target->GetWidth());
    assert(Graphics::VirtualGraphic().GetContextHeight() == render_target->GetHeight());
    const Color* frame_buffer = Graphics::VirtualGraphic().GetRenderContext().GetBuffer();
    render_target->OnPresent(frame_buffer);
}

void XRender::Camera::Render()
{
    SyncGraphicsCameraData();
    Graphics::VirtualGraphic().Execute();
    Present();
}