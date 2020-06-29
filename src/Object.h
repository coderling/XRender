#pragma once
#include <geometry.h>

#include "Mesh.h"
#include "Renderer.h"

namespace XRender
{

class Object final
{
public:
    Object();
    ~Object();
public:
    void SetPosition(const Vec3f& position);
    const Vec3f& GetPosition() const;
    void SetRotation(const Vec3f& rotation);
    const Vec3f& GetRotation() const;
    void SetScale(const Vec3f& scale);
    const Vec3f& GetScale() const;
private:
    void UpdateRendererMatrix();

public:
    std::unique_ptr<Renderer> renderer;
private:
    Vec3f position;
    Vec3f rotation;
    Vec3f scale;
    Matrix worldMatrix;
    friend class Scene;
};

}