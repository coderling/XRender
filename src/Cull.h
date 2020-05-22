#pragma once
#include <vector>

#include "Camera.h"
#include "Scene.h"
#include "Renderer.h"

class Cull
{
public:
    void CullRenderers(const Camera& cam, Scene* scenes);
private:
    std::vector<Renderer> renderers;
};