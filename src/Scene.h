#pragma once
#include <vector>

#include "Object.h"
#include "Lighting.h"
#include "Bounds.h"

namespace XRender
{

class Scene final
{
public:
    Scene();
    const std::vector<Renderer*>& GetActiveRenderers() const;
    void AddObject(std::unique_ptr<Object> object);
    Lighting::Light* GetLight(const uint32_t& index);
    const Bounds& GetSceneBounds();
private:
    Bounds bounds;
    uint32_t mesh_count;
    std::vector<Renderer*> renderers;
    std::vector<std::unique_ptr<Object>> objects;
    Lighting::Light lights[Lighting::max_light_num];
};

}