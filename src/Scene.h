#pragma once
#include <vector>

#include "Object.h"

namespace XRender
{

class Scene final
{
public:
    const std::vector<Renderer*>& GetActiveRenderers() const;
    void AddObject(std::unique_ptr<Object> object);
private:
    std::vector<Renderer*> renderers;
    std::vector<std::unique_ptr<Object>> objects;
};

}