#pragma once
#include <geometry.h>

class Camera
{
private:
    bool isPerspectiveProj;
    Matrix view;
    Matrix proj;
public:
    Matrix GetViewMatrix();
    Matrix GetProjMatrix();
    Matrix GetOrthographicMatrix();
    void LookAt(Vec3f pos, Vec3f up, Vec3f look);
    void SetIsPerspective(bool isPerProj);
    void SetFieldOfView(float angle);
    void SetPerspective(float angle, float aspect, float near, float far);
    void SetViewPort(float x, float y, float w, float h);
};