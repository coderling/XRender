#pragma once
#include <geometry.h>

#include "RenderDevice.h"
#include "RenderContext.h"
#include "ViewFrustum.h"
#include "GraphicsEnum.h"

namespace XRender
{

class Camera final
{
public:
	static Camera& MainCamera();
public:
    Camera();
    const Matrix& GetViewMatrix() const;
    const Matrix& GetProjMatrix() const;
    void LookAt(const Vec3f& pos, const Vec3f& up, const Vec3f& look);
    void SetIsPerspective(const bool& isPerProj);
    void SetFieldOfView(const float& angle);
    void SetPerspective(const float& angle, const float& near, const float& far);
    void SetOrthgraphic(const float& near, const float& far);
    void SetViewPort(const float& x, const float& y, const float& w, const float& h);
    void Update();
    void SyncGraphicsCameraData() const;
    void Present();
    const Frustum& GetFrustum() const;
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
};
}