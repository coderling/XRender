#pragma once
#include <geometry.h>

#include "RenderTarget.h"
#include "RenderContext.h"

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
    void SetRenderTarget(std::unique_ptr<RenderTarget> target);
    void Update();
    void Present();
private:
    void ReCaculateProjectMatrix();
    void CaculatePerspective();
    Matrix CaculateOrthgraphic(const float& left, const float& right, const float& top, const float& bottom, const float& near, const float& far) const;
    bool is_perspective;
    Matrix view;
    Matrix proj;
    Matrix view_port;
    float angle;
    float aspect;
    float near_plane;
    float far_plane;
    std::unique_ptr<RenderTarget> render_target; 
};
}