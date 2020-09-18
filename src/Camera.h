#pragma once
#include <geometry.h>

#include "RenderDevice.h"
#include "RenderContext.h"
#include "ViewFrustum.h"
#include "GraphicsEnum.h"
#include "Transform.h"

namespace XRender
{

class Camera final
{
public:
	static Camera& MainCamera();
public:
    Camera();
    const Matrix& ViewMatrix() const;
    const Matrix& InvertViewMatrix() const;
    const Matrix& ProjMatrix() const;
    void LookAt(const Vec3f& pos, const Vec3f& up, const Vec3f& target);
    void SetViewPort(const float& x, const float& y, const float& w, const float& h);
    void Update();
    void SyncGraphicsCameraData() const;
    void Present();
    const Frustum& GetFrustum() const;
    const Transform& Transform() const;
    const float& Near() const;
    const float& Far() const;
    const float& Angle() const;
    void Near(const float& near);
    void Far(const float& far);
    void Angle(const float& angle);
    void IsPerspective(const bool& isPerProj);
    const bool& IsPerspective();
    const float& Aspect()const;
private:
    void ReCaculateProjectMatrix();
    void CaculatePerspective();
    void CaculateOrthgraphic();
    bool is_perspective;
    Matrix invert_view;
    Matrix view;
    Matrix proj;
    Matrix view_port;
    float angle;
    float aspect;
    float near_plane;
    float far_plane;
    Frustum frustum;
    int clear_flag = GraphicsEnum::EClearFlag::Clear_Depth | GraphicsEnum::EClearFlag::Clear_Color;

    XRender::Transform transform;
};
}