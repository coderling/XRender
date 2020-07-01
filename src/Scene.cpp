#include "Scene.h"

XRender::Scene::Scene():renderers()
{}

const std::vector<XRender::Renderer*>& XRender::Scene::GetActiveRenderers() const
{
    return renderers;
}

void XRender::Scene::AddObject(std::unique_ptr<Object> object)
{
    if(object->renderer != nullptr)
    {
        renderers.emplace_back(object->renderer.get());
    }
    object->SetPosition(Vec3f_Zero);
    objects.emplace_back(std::move(object));
}