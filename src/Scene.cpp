#include "Scene.h"

XRender::Scene::Scene():renderers()
{}

const std::vector<XRender::Renderer*>& XRender::Scene::GetActiveRenderers() const
{
    return renderers;
}

void XRender::Scene::AddObject(std::unique_ptr<Object> object)
{
    bounds.Expand(object->Transform().GetPosition());
    if(object->renderer != nullptr)
    {
        if(object->renderer->mesh != nullptr)
        {
            bounds.Expand(object->renderer->mesh->bounds);
        }
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