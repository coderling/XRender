#pragma once
#include <vector>
#include <functional>
#include <stdint.h>
#include <memory>

#include "Scene.h"
#include "Camera.h"
#include "GraphicsEnum.h"
#include "RenderTexture.h"

namespace XRender
{

class Pipeline
{
public:
    Pipeline();
    virtual ~Pipeline();
    void Prepare();
    void BaseRender(const std::vector<Camera*>& camreas);
    virtual void PreRender(Camera* camera);
    virtual void Render(Camera* camera);
    virtual void PostRender(Camera* camera);
    void DrawRenderers(const std::vector<Renderer*>& renderers, Camera* camera);

    std::unique_ptr<Scene> scene;
};

struct PipelineInitializeData
{
public:
    uint32_t width;
    uint32_t height;
    std::string title;
    std::function<void()> tick_func = nullptr;
    Pipeline* pipeline = nullptr;
};

}