#pragma once
#include <functional>

#include "Pipeline.h"
#include "Camera.h"

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
private:
    std::function<void()> tick_func;
    bool quit;
    Pipeline *pPipeline;
};

}
