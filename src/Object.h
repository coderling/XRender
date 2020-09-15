#pragma once
#include <geometry.h>

#include "Mesh.h"
#include "Renderer.h"
#include "Transform.h"

namespace XRender
{

class Object final
{
public:
    Object();
    ~Object();
    void SetRenderer(std::unique_ptr<Renderer> renderer);
    Renderer* Renderer();
    Transform& Transform();

private:
    std::unique_ptr<XRender::Renderer> renderer;
    XRender::Transform transform;
    friend class Scene;
};

}