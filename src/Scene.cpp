#include "Scene.h"


const std::vector<XRender::Renderer*>& XRender::Scene::GetActiveRenderers() const
{
    return renderers;
}

void XRender::Scene::AddObject(std::unique_ptr<Object> object)
{
    objects.emplace_back(std::move(object));
    if(object->renderer != nullptr)
    {
        renderers.emplace_back(object->renderer.get());
    }
}