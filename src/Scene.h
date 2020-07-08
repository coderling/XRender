#pragma once
#include <vector>

#include "Object.h"
#include "Lighting.h"

namespace XRender
{

class Scene final
{
public:
    Scene();
    const std::vector<Renderer*>& GetActiveRenderers() const;
    void AddObject(std::unique_ptr<Object> object);
    Lighting::Light* GetLight(const uint32_t& index);
private:
    std::vector<Renderer*> renderers;
    std::vector<std::unique_ptr<Object>> objects;
    Lighting::Light lights[Lighting::max_light_num];
};

}