#pragma once
#include <vector>

#include "Scene.h"

class Pipeline
{
public:
    virtual ~Pipeline();
    virtual void PreRender();
    virtual void Render();
    virtual void PostRender();

private:
    std::vector<Scene> activeScenes;
};