#include "Cull.h"
#include "ViewFrustum.h"

XRender::Cull& XRender::Cull::GlobalCull()
{
	static XRender::Cull global_cull;
	return global_cull;
}

const std::vector<XRender::Renderer*>& XRender::Cull::CullRenderers(const Camera &cam, const Scene* scene)
{
    static Frustum frustum;
    frustum.Update(cam);
    renderers.clear();
    const auto& active_renderers = scene->GetActiveRenderers();
    for(auto renderer : active_renderers)
    {
        renderers.emplace_back(renderer);
    }
    return renderers;
}