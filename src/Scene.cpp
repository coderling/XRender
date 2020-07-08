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
    objects.emplace_back(std::move(object));
}
   
XRender::Lighting::Light* XRender::Scene::GetLight(const uint32_t& index)
{
    if(index < Lighting::max_light_num)
    {
        return &lights[index];
    }
    return nullptr;
}