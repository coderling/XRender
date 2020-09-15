#pragma once
#include <functional>
#include <unordered_set>

#include "Pipeline.h"
#include "Camera.h"
#include "RenderTexture.h"

namespace XRender 
{

class XRender final
{
public:
    XRender();
    ~XRender();
    void Initialize(PipelineInitializeData& pipeline_data);
    void Loop();
    void Exit();
    Pipeline* GetPipeline() const;
    void RegisterCamera(Camera* camera);
    void UnRegisterCamera(Camera* camera);
    void RegistrTickFunc(std::function<void()> tick);
    void UnRegistrTickFunc(std::function<void()> tick);
private:
    void InnerTick();
    void Present() const;
    void TickCamera() const;
    std::vector<std::function<void()>> ticks;
    bool quit;
    
    Pipeline *pPipeline;
    std::vector<Camera*> cameras;
};

}
