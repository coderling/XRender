#pragma once
#include <vector>
#include <functional>

#include "Scene.h"
#include "RenderTarget.h"

namespace XRender
{

class Pipeline
{
public:
    virtual ~Pipeline();
    virtual void PreRender();
    virtual void Render();
    virtual void PostRender();
    void DrawRenderers(const std::vector<Renderer*>& renderers);
    
    std::unique_ptr<Scene> scene;
};

struct PipelineInitializeData
{
public:
    RenderTarget* render_target = nullptr;
    std::function<void()> tick_func = nullptr;
    Pipeline* pipeline = nullptr;
};

}