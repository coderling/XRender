#pragma once
#include <vector>

#include "Camera.h"
#include "Scene.h"
#include "Renderer.h"

namespace XRender
{

class Cull
{
public:
	static Cull& GlobalCull();
    const std::vector<Renderer*>& CullRenderers(const Camera& cam, const Scene* scene);
private:
    std::vector<Renderer*> renderers;
};
}